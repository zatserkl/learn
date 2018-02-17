// https://stackoverflow.com/questions/936684/getting-the-class-name-from-a-static-method-in-java

/**
 * Usage:
 *
 * $ ls get_class_name/
 * GetClassName.java
 * 
 * $ javac get_class_name/GetClassName.java
 * $ java get_class_name.GetClassName
 * 
 * get full name (with the package) from the static method
 * GetClassName.class.getName() = get_class_name.GetClassName
 * 
 * get simple name from the static method
 * GetClassName.class.getSimpleName() = GetClassName
 * 
 * get name from the instance of the class
 * GetClassName getClassName = new GetClassName();
 * getClassName.getName() = get_class_name.GetClassName
*/

package get_class_name;

public class GetClassName {
    public String getName() {
        // return getClass().getName();     // the same as this.getClass().getName()
        return this.getClass().getName();
    }
    public static void main(String[] args)
    {
        System.out.println("\nget full name (with the package) from the static method");
        System.out.println("GetClassName.class.getName() = " + GetClassName.class.getName());

        System.out.println("\nget simple name from the static method");
        System.out.println("GetClassName.class.getSimpleName() = " + GetClassName.class.getSimpleName());

        System.out.println("\nget name from the instance of the class");
        GetClassName getClassName = new GetClassName();
        System.out.println("GetClassName getClassName = new GetClassName();");
        System.out.println("getClassName.getName() = " + getClassName.getName());
    }
}
