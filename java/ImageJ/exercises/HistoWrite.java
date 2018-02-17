import ij.ImagePlus;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;
import ij.process.ByteProcessor;

import ij.IJ;       // to use IJ.log

// stuff to write the output file
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.IOException;

public class HistoWrite implements PlugInFilter {

    ImagePlus im;

    public int setup(String arg, ImagePlus im) {	// NB: not String[] args
        // IJ.log("arg = " + arg);			// some comment
        this.im = im;
        return DOES_8G + NO_CHANGES;
    }

    public void run(ImageProcessor ip)
    {
        IJ.log("\n");

        int[] hist = ip.getHistogram();

        // inspect the histogram

        int hmax = hist[0];
        for (int i=0; i<hist.length; ++i) if (hist[i] > hmax) hmax = hist[i];

        IJ.log("hist.length = " + hist.length + " hmax = " + hmax);

	// Write the histogram to the file

	// look for output file in dir ~/Applications/ImageJ/
	String ofname = im.getShortTitle() + ".histo.dat";

	// open output file

	try {
	    FileWriter fileWriter = new FileWriter(ofname);
	    PrintWriter printWriter = new PrintWriter(fileWriter);

	    for (int i=0; i<hist.length; i++) {
		printWriter.printf("%d\n", hist[i]);
	    }

	    printWriter.close();

	    IJ.log("Wrote output file " + ofname);
	}
	catch(IOException e) {
	    System.out.println(e);
	}
    }
}
