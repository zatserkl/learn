package equalstest;

import equalstest.Time;

public class EqualsTest {

    public static void main(String[] args)  // comp. error if no (String[] args)
    {
        System.out.println("test a simple variables");
        int a = 5;
        int b = a;

        // change a
        a = 10;

        // look at b
        System.out.println("a = " + a + " b = " + b);

        System.out.println("\nplay with Time now");

        Time time1 = new Time(1, 2, 3.14);
        System.out.println("time1.hour = " + time1.hour);

        // Note that following doesn't involve a copy constructor call as 
        // non-primitive variables are just references.
        Time time2 = time1;                     // time2 is an object reference
        System.out.println("Set time2 = time1. Now time2.hour = " + time2.hour);

        time1.hour = 11;
        System.out.println("change time1.hour to " + time1.hour);

        System.out.println("time2.hour = " + time2.hour);

        // (time1 == time2) == true;
        System.out.println("time1 == time2: " + (time1 == time2));

        // time1.equals(time2) == true;
        System.out.println("time1.equals(time2) = " + time1.equals(time2));

        System.out.println("\nNow create a different Time object with the same values as time1\n");
        Time time3 = new Time(time1);
        System.out.println("time1: " + time1);
        System.out.println("time3: " + time3);

        // (time1 == time3) == false: time1  and time3 do not refer to the same variable
        System.out.println("time1 == time3: " + (time1 == time3));

        // time1.equals(time3) == false;
        System.out.println("time1.equals(time3) = " + time1.equals(time3));
    }
}
