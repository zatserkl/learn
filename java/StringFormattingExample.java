public class StringFormattingExample {
    static public void main(String[] args)
    {
	double val_pi = 3.14159;
	System.out.println(String.format("value of pi = %.2f", val_pi));

	double val_e = 2.71828;
	System.out.println(String.format("value of e = %.2f", val_e));

	System.out.println(String.format("value of pi = %.2f, value of e = %.2f", val_pi, val_e));
    }
}
