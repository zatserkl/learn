// based on https://www.javacodegeeks.com/2015/09/how-to-create-and-destroy-objects.html
// AZ: I made class fields static and introduced a static initialization block

// package com.javacodegeeks.advanced.construction;
 
public class InitializationWithDefaults {
    static private boolean booleanMember;
    static private byte byteMember;
    static private short shortMember;
    static private int intMember;
    static private long longMember;
    static private char charMember;
    static private float floatMember;
    static private double doubleMember;
    static private Object referenceMember;
 
    // public InitializationWithDefaults()
    static {   // initialization block (to save on typing of the class name)
        System.out.println( "booleanMember = " + booleanMember );
        System.out.println( "byteMember = " + byteMember );
        System.out.println( "shortMember = " + shortMember );
        System.out.println( "intMember = " + intMember );
        System.out.println( "longMember = " + longMember );
        System.out.println( "charMember = " +
            Character.codePointAt( new char[] { charMember }, 0  ) );
        System.out.println( "floatMember = " + floatMember );
        System.out.println( "doubleMember = " + doubleMember );
        System.out.println( "referenceMember = " + referenceMember );
    }

    public static void main(String[] args) {
        // final InitializationWithDefaults initializationWithDefaults =
        //     new InitializationWithDefaults();
    }
}
