/*******************************************************************************
 * This software is provided as a supplement to the authors' textbooks on digital
 *  image processing published by Springer-Verlag in various languages and editions.
 * Permission to use and distribute this software is granted under the BSD 2-Clause 
 * "Simplified" License (see http://opensource.org/licenses/BSD-2-Clause). 
 * Copyright (c) 2006-2016 Wilhelm Burger, Mark J. Burge. All rights reserved. 
 * Visit http://imagingbook.com for additional details.
 *******************************************************************************/

//--AZ package Ch02_ImageJ;

import ij.ImagePlus;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;

import ij.IJ;       // to use IJ.log

/**
 * This is a minimal ImageJ plugin (PlugInFilter) that inverts an
 * 8-bit grayscale (byte) image.
 * @author WB
 */
public class My_Inverter_A implements PlugInFilter {

    public int setup(String args, ImagePlus im) {
        return DOES_8G; // this plugin accepts 8-bit grayscale images 
    }

    public void run(ImageProcessor ip) {
        int M = ip.getWidth();
        int N = ip.getHeight();

        IJ.log("Width: " + M + " pixels\nHeight: " + N + " pixels");

        // iterate over all image coordinates
        for (int u = 0; u < M; u++) {
            for (int v = 0; v < N; v++) {
                //
                // NB: getPixel(i_width, i_height): "by column"
                //
                // int p = ip.getPixel(u, v);      // uses ImageProcessor ip to get
                // ip.putPixel(u, v, 255 - p);     // and to put the pixel
                int p = ip.get(u, v);        // put is faster than getPixel: no range check
                ip.set(u, v, 255 - p);       // set is faster than puPixel
            }
        }
    }

}

