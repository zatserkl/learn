// based on Answer #8 at https://stackoverflow.com/questions/5614562/how-to-do-the-equivalent-of-pass-by-reference-for-primitives-in-java

import java.util.concurrent.atomic.AtomicInteger;


public class PrimitivePassByReferenceSample
{
    /**
     * @param args
     */
    public static void main(String[] args)
    {
        AtomicInteger myNumber = new AtomicInteger(0);
        System.out.println("MyNumber before method Call:" + myNumber.get());

        PrimitivePassByReferenceSample temp = new PrimitivePassByReferenceSample() ;

        temp.changeMyNumber(myNumber);
        System.out.println("MyNumber After method Call:" + myNumber.get());
    }

    void changeMyNumber(AtomicInteger myNumber) {
        myNumber.getAndSet(100);
    }
}
