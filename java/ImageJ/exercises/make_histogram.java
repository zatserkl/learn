import ij.ImagePlus;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;
import ij.process.ByteProcessor;

import ij.IJ;       // to use IJ.log

public class make_histogram implements PlugInFilter {

    ImagePlus im;

    public int setup(String arg, ImagePlus im) {
        this.im = im;
        return DOES_8G + NO_CHANGES;
    }


    public void run(ImageProcessor ip)
    {
        int[] hist = ip.getHistogram();
        int K = hist.length;

        int hmax = hist[0];
        for (int i=0; i<hist.length; ++i) if (hist[i] > hmax) hmax = hist[i];

        // IJ.log("hist.length = " + hist.length + " hmax = " + hmax);
        IJ.log("hist.length = " + hist.length + " hmax = " + hmax + " ip.getHistogramMax() = " + ip.getHistogramMax());

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
