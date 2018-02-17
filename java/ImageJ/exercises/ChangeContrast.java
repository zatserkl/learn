import ij.ImagePlus;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;
import ij.process.ByteProcessor;

import ij.IJ;       // to use IJ.log

public class ChangeContrast implements PlugInFilter {

    ImagePlus im;

    public int setup(String arg, ImagePlus im) {        // NB: not String[] args
        // IJ.log("arg = " + arg);
        this.im = im;
        return DOES_8G + NO_CHANGES;
    }

    public static final int threshold = 32;
    // public static final double percentContrast = 0.30;
    public static final double percentContrast = 0.50;

    public void run(ImageProcessor ip)
    {
        IJ.log("\n");

        String addInfo = "";
        addInfo += " percentContrast = " + percentContrast;

        int[] hist = ip.getHistogram();

        // inspect the histogram

        int hmax = hist[0];
        for (int i=0; i<hist.length; ++i) if (hist[i] > hmax) hmax = hist[i];

        IJ.log("hist.length = " + hist.length + " hmax = " + hmax);

        /** get the mean and sigma

	    Our histogram is a non-normalized Probability Density Function. 
	    Normalization factor is an integral over pdf: a sum over all histogram values.
	    Ex = Sum(i * pdf) / Norm
	    Exx = Sum(i*i * pdf) / Norm
	    Mean = Ex
	    Var = Exx - Ex*Ex
	    StdDev = sqrt(Var)
	 */
	
	double norm = 0;
	double sum_x = 0;
	double sum_xx = 0;
	for (int i=0; i<hist.length; i++) {
	    double pdf = hist[i];
	    norm += pdf;
	    sum_x += i * pdf;
	    sum_xx += i*i * pdf;
	}
	double mean = sum_x / norm;
	double variance = sum_xx / norm - mean*mean;
	double sigma = Math.sqrt(variance);
	// IJ.log("norm = " + norm + " sum_x = " + sum_x + " sum_xx = " + sum_xx);
	IJ.log(String.format("mean = %.1f sigma = %.1f", mean, sigma));

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

        ImageProcessor ipCopy = new ByteProcessor(ip.getWidth(), ip.getHeight());
        for (int ih=0; ih<ip.getHeight(); ih++) {
            for (int iw=0; iw<ip.getWidth(); iw++) {
                int value = ip.get(iw, ih);
                // apply cut
                // value -= threshold;

                double dValue = percentContrast*(value - mean);
                value += dValue;

                if (value < 0) value = 0;
                if (value >= 255) value = 255;
                ipCopy.set(iw, ih, value);
            }
        }

        // compose the title
        String ipCopyTitle = "Copy of " + im.getShortTitle() + addInfo;

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
