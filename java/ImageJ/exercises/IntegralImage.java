import ij.ImagePlus;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;
import ij.process.ByteProcessor;

import ij.IJ;               // to use IJ.log

import java.awt.Point;
import java.util.*;         // Map, HashMap

/**
  * This class represents an integral image. Intended to be used as an ImageJ plugin.
  *
  * @author Andriy Zatserklyaniy
  * @version 2017/07/25
  */
public class IntegralImage implements PlugInFilter {

    ImagePlus im;

    //
    // Hash table for the recursive version of the IntegralImage
    //
    //-- Map<Point, Object> hash = new HashMap<Point, Object>();
    //--int-- Map<Point, Integer> hash = new HashMap<Point, Integer>();   // NB: HashMap<> does not supported in this version
    private final Map<Point, Long> hash = new HashMap<Point, Long>();   // NB: HashMap<> does not supported in this version
    int hashHit = 0;
    int hashMiss = 0;

    /**
      * @param u is the pixel position along the width
      * @param v is the pixel position along the height
      */
    long integralImageRecurse(ImageProcessor ip, int u, int v)
    {
        // NB: for the whole image
        // u is width
        // v is height

        // IJ.log("    u = " + u + " v = " + v);

        if (u < 0 || v < 0) return 0;

        // IJ.log("(" + u + "," + v + ")");

        Point point = new Point(u, v);
        long value = 0;

        if (hash.containsKey(point)) {
            ++hashHit;
            //-- value = ((Number) hash.get(point)).intValue();
            // value = (int) hash.get(point); // error: incompatible types: Object cannot be converted to int
            //-- value = (Integer) hash.get(point);
            value = hash.get(point);
        }
        else {
            ++hashMiss;
            value = integralImageRecurse(ip, u-1, v) + integralImageRecurse(ip, u, v-1)
                - integralImageRecurse(ip, u-1, v-1) + ip.getPixel(u, v);
            hash.put(point, value);
        }

        return value;
    }

    /**
      * @param u1 is the pixel to start along the width of the rectangular area
      * @param u2 is the pixel to stop along the width of the rectangular area
      * @param v1 is the pixel to start along the height of the rectangular area
      * @param v2 is the pixel to stop along the height of the rectangular area
      */
    long integralImageIterative(ImageProcessor ip, int u1, int v1, int u2, int v2)
    {
        long integral = 0;
        for (int u=u1; u<u2; ++u)
            for (int v=v1; v<v2; ++v)
                integral += ip.getPixel(u,v);

        return integral;
    }

    // Array of point-to-point integrals: linear and square (to get the variance)
    private long[][] s1, s2;

    /**
      * @param u is the width of the rectangular area
      * @param v is the height of the rectangular area
      */
    long integralImageMatrix(ImageProcessor ip, int u, int v)
    {
        s1 = new long[u][v];    // [width][height]
        s2 = new long[u][v];

        //
        // fill in the three steps:
        //

        // initialize top-left corner
        s1[0][0] = ip.getPixel(0,0);
        s2[0][0] = s1[0][0] * s1[0][0];

        // IJ.log("fill the line v = 0");

        // fill the line v = 0
        for (int iu=1; iu<u; ++iu) {
            long value = ip.getPixel(iu, 0);
            s1[iu][0] = s1[iu-1][0] + value;
            s2[iu][0] = s2[iu-1][0] + value*value;
        }

        // IJ.log("fill the rest of the lines");

        // fill the rest of lines
        for (int iv=1; iv<v; ++iv) {
            // go line-by-line from top to bottom
            long value = ip.getPixel(0, iv);        // fill the first cell in the row
            s1[0][iv] = s1[0][iv-1] + value;
            s2[0][iv] = s2[0][iv-1] + value*value;
            for (int iu=1; iu<u; ++iu) {
                value = ip.getPixel(iu, iv);
                //s1[iu][iv] = s1[iu-1][iv-1] + value;
                //s2[iu][iv] = s2[iu-1][iv-1] + value*value;
		//-- s1[iu][iv] = s1[iu-1][iv] + s1[iu][iv-1] - s1[iu-1][iv-1] + value;
		//-- s2[iu][iv] = s2[iu-1][iv] + s2[iu][iv-1] - s2[iu-1][iv-1] + value*value;
		s1[iu][iv] = s1[iu-1][iv] + s1[iu][iv-1] - s1[iu-1][iv-1] + value;
		s2[iu][iv] = s2[iu-1][iv] + s2[iu][iv-1] - s2[iu-1][iv-1] + value*value;
            }
        }

        // // debug output
        // for (int iv=0; iv<v; ++iv) {
        //     for (int iu=0; iu<u; ++iu) {
        //         IJ.log(s1[iu][iv] + " ");
        //     }
        //     IJ.log("\n");
        // }

        // for (int iv=0; iv<v; ++iv) {
        //     for (int iu=0; iu<u; ++iu) {
        //         IJ.log("ip.getPixel(" + iu + "," + iv + ") = " + ip.getPixel(iu, iv));
        //     }
        // }

        return s1[u-1][v-1];
    }

    public int setup(String arg, ImagePlus im) {
        this.im = im;
        return DOES_8G + NO_CHANGES;
    }


    public void run(ImageProcessor ip)
    {
        int width = ip.getWidth();
        int height = ip.getHeight();

        width = 4;
        height = 3;

        // NB: in my recursive implementation the parameters are pixel's positions
        long integralImageRecurseTot = integralImageRecurse(ip, width-1, height-1); // NB: width-1 and height-1

        IJ.log("\nintegralImageRecurseTot = " + integralImageRecurseTot + " hashHit = " + hashHit + " hashMiss = " + hashMiss);

        long integralImageIterativeTot = integralImageIterative(ip, 0, 0, width, height);

        IJ.log("\nintegralImageIterativeTot = " + integralImageIterativeTot);

        long integralImageMatrixTot = integralImageMatrix(ip, width, height);
        // long integralImageMatrixTot = integralImageMatrix(ip, 4, 3);

        IJ.log("\nintegralImageMatrixTot = " + integralImageMatrixTot);

        //
        // histogram
        //

        int[] hist = ip.getHistogram();
        int K = hist.length;

        int hmax = hist[0];
        for (int i=0; i<hist.length; ++i) if (hist[i] > hmax) hmax = hist[i];

        // IJ.log("hist.length = " + hist.length + " hmax = " + hmax);
        IJ.log("\nhist.length = " + hist.length + " hmax = " + hmax + " ip.getHistogramMax() = " + ip.getHistogramMax());

        //
        // create the histogram image for maxHeight pixels.
        //

        int maxHeight = 400;
        ImageProcessor hip = new ByteProcessor(K, maxHeight);
        hip.setValue(255);  // white
        hip.fill();

        int black = 0;      // black color

        // fill the histogram
        for (int ibin=0; ibin<hist.length; ibin++) {
            int value = hist[ibin] * maxHeight / hmax;
            for (int iheight=0; iheight<value; iheight++) {
                hip.putPixel(ibin, maxHeight - iheight, black);
            }
        }

        // compose the title
        String imTitle = im.getShortTitle();
        String hTitle = "Histogram of " + imTitle;

        // display the histogram
        ImagePlus him = new ImagePlus(hTitle, hip);
        him.show();
    }
}
