import ij.ImagePlus;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;
import ij.process.ByteProcessor;

import ij.IJ;       // to use IJ.log

public class copy_play implements PlugInFilter {

    ImagePlus im;

    public int setup(String arg, ImagePlus im) {
        // IJ.log("arg = " + arg);
        this.im = im;
        return DOES_8G + NO_CHANGES;
    }

    public static final int threshold = 32;    

    public void run(ImageProcessor ip)
    {
        IJ.log("\n");

        int[] hist = ip.getHistogram();

        int hmax = hist[0];
        for (int i=0; i<hist.length; ++i) if (hist[i] > hmax) hmax = hist[i];

        IJ.log("hist.length = " + hist.length + " hmax = " + hmax);

        //
        // create the histogram image for maxHeight pixels.
        //

        // int maxHeight = 400;
        int maxHeight = 256;

        int black = 0;      // black color

        ImageProcessor hip = new ByteProcessor(hist.length, maxHeight);
        hip.setValue(255);  // white
        hip.fill();

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

        //
        // make a copy and modify it
        //

        // some stats
        IJ.log("ip.getBitDepth() = " + ip.getBitDepth());
        IJ.log("ip.getWidth() = " + ip.getWidth() + " ip.getHeight() = " + ip.getHeight());

        // copy the image

        // int threshold = 32;
        // int threshold = 64;

        ImageProcessor ipCopy = new ByteProcessor(ip.getWidth(), ip.getHeight());
        for (int ih=0; ih<ip.getHeight(); ih++) {
            for (int iw=0; iw<ip.getWidth(); iw++) {
                int value = ip.get(iw, ih);
                // apply cut
                value -= threshold;
                if (value < 0) value = 0;
                ipCopy.set(iw, ih, value);
            }
        }

        // compose the title
        String ipCopyTitle = "Copy of " + im.getShortTitle();

        // display the copy
        ImagePlus imCopy = new ImagePlus(ipCopyTitle, ipCopy);
        imCopy.show();

        //
        // histogram of the modified image
        //

        IJ.log("imCopy.getShortTitle() = " + imCopy.getShortTitle());

        int[] histCopy = ipCopy.getHistogram();

        ImageProcessor hipCopy = new ByteProcessor(histCopy.length, maxHeight);
        hipCopy.setValue(255);  // white
        hipCopy.fill();

        int hmaxCopy = histCopy[0];
        for (int i=0; i<histCopy.length; ++i) if (histCopy[i] > hmaxCopy) hmaxCopy = histCopy[i];

        // fill the histogram
        for (int ibin=0; ibin<histCopy.length; ibin++) {
            int value = histCopy[ibin] * maxHeight / hmaxCopy;
            for (int iheight=0; iheight<value; iheight++) {
                hipCopy.putPixel(ibin, maxHeight - iheight, black);
            }
        }

        // compose the title
        // String imCopyTitle = imCopy.getShortTitle();     // returns the first word of the title
        String imCopyTitle = imCopy.getTitle();             // returns the whole title
        String hTitleCopy = "Histogram of " + imCopyTitle;

        // display the histogram
        ImagePlus himCopy = new ImagePlus(hTitleCopy, hipCopy);
        himCopy.show();
    }
}
