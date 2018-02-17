/**
Prints the Greek Alphabet (unicode characters).
NB: There is no a symbol for decilmal 930, so the question mark will be printed.

To compile and execute:

javac GreekAlphabet.java
java GreekAlphabet

To check style:

java -jar checkstyle-8.4-all.jar -c /google_checks.xml GreekAlphabet.java
 */

public class GreekAlphabet {
    public static void main(String[] args) {
	System.out.println("NB: There is no symbol for decimal 930");
	// for (int i=913; i<=937; ++i) System.out.print((char) i + " ");
	// for (int i=913; i<=976; ++i) System.out.print((char) i + " ");
	for (int i=913; i<=937; ++i) System.out.print((char) i + " ");
	for (int i=945; i<=969; ++i) System.out.print((char) i + " ");
	System.out.println();
    }
}
