// http://docs.oracle.com/javase/tutorial/essential/io/file.html

public class BufferedIOMethodsExample
{
    public static void main(String[] args)
    {
        final String fname;
        if (args.length > 0) fname = args[0];
        else fname = BufferedIOMethodsExample.class.getName() + ".txt";

        // get the Path using fname
        java.nio.file.Path path = java.nio.file.Paths.get(fname);   // NB: Path ... = Paths
        System.out.println("path = " + path);

        java.nio.charset.Charset charset = java.nio.charset.Charset.forName("US-ASCII"); // optional

        //
        // write file
        //

        System.out.println("\nwrite a new file " + path);

        try (java.io.BufferedWriter writer = java.nio.file.Files.newBufferedWriter(path, charset)) // try-with-resources
        {
            //writer.write(s, 0, s.length());
            writer.write("This is a line number 1\n");
            writer.write("This is a line number 2\n");
        }
        catch (java.io.IOException e) {
            System.err.format("java.io.IOException: %s%n", e);
        }

        //
        // read file
        //

        System.out.println("\nread the file " + path);

        try (java.io.BufferedReader reader = java.nio.file.Files.newBufferedReader(path, charset)) // try-with-resources
        {
            String line = null;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        }
        catch (java.io.IOException e) {
            System.err.format("java.io.IOException: %s%n", e);
        }
    }
}
