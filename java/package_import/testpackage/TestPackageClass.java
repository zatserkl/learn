package testpackage;

import testpackage.MyClassSamePackage;
import testpackage2.MyClass;

public class TestPackageClass {
    public static void main(String[] args) {
        System.out.println("Hello from testpackage.TestPackageClass!");
        System.out.println("Now accessing " + MyClassSamePackage.name);
        System.out.println("Now accessing " + MyClass.name);
    }
}
