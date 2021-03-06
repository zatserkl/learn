/*******************************************************************************
 * This software is provided as a supplement to the authors' textbooks on digital
 *  image processing published by Springer-Verlag in various languages and editions.
 * Permission to use and distribute this software is granted under the BSD 2-Clause 
 * "Simplified" License (see http://opensource.org/licenses/BSD-2-Clause). 
 * Copyright (c) 2006-2016 Wilhelm Burger, Mark J. Burge. All rights reserved. 
 * Visit http://imagingbook.com for additional details.
 *******************************************************************************/

//--AZ package Ch02_ImageJ;

import ij.IJ;                       // to use IJ.getImage, IJ.error and IJ.log
import ij.ImagePlus;
import ij.plugin.PlugIn;
import ij.process.ImageProcessor;

// import ij.IJ;       // to use IJ.log

/**
 * This plugin does the same as {@link My_Inverter_A} but is based on the {@link ij.plugin.PlugIn}
 * instead of the {@link ij.plugin.filter.PlugInFilter} interface. Its advantage is that only one
 * method (run()) must be implemented. Disadvantage is that testing if an image
 * is currently open and is of the proper type must be explicitly coded.
 * @author WB
 */
public class My_Inverter_B implements PlugIn {

    public void run(String args) {
        ImagePlus im = IJ.getImage(); // WindowManager.getCurrentImage();

        if (im.getType() != ImagePlus.GRAY8) {
            IJ.error("8-bit grayscale image required"); 
            return;
        }

        ImageProcessor ip = im.getProcessor();
        int M = ip.getWidth();
        int N = ip.getHeight();

        IJ.log("Width: " + M + " pixels\nHeight: " + N + " pixels");

        // iterate over all image coordinates
        for (int u = 0; u < M; u++) {
            for (int v = 0; v < N; v++) {
                int p = ip.get(u, v);       // get is faster than getPixel
                ip.set(u, v, 255 - p);      // set is faster than putPixel
            }
        }

        im.updateAndDraw();             // redraw the modified image
    }

}
