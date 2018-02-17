Java directory structure to use package and import
https://stackoverflow.com/questions/631682/help-with-packages-in-java-import-does-not-work
Answer #36

Okay, just to clarify things that have already been posted.
You should have the directory com, containing the directory company, containing the directory example, containing the file MyClass.java.

From the folder containing com, run:
$ javac com\company\example\MyClass.java

Then:
$ java com.company.example.MyClass
Hello from MyClass!

These must both be done from the root of the source tree. Otherwise, javac and java won't be able to find any other packages (in fact, java wouldn't even be able to run MyClass).

A short example

I created the folders "testpackage" and "testpackage2". Inside testpackage, I created TestPackageClass.java containing the following code:

package testpackage; 

import testpackage2.MyClass; 

public class TestPackageClass { 
        public static void main(String[] args) { 
                System.out.println("Hello from testpackage.TestPackageClass!"); 
                System.out.println("Now accessing " + MyClass.NAME); 
        } 
}

Inside testpackage2, I created MyClass.java containing the following code:

package testpackage2; 

public class MyClass { 
        public static String NAME = "testpackage2.MyClass"; 
}

From the directory containing the two new folders, I ran:
C:\examples>javac testpackage\*.java

C:\examples>javac testpackage2\*.java


Then:
C:\examples>java testpackage.TestPackageClass
Hello from testpackage.TestPackageClass!
Now accessing testpackage2.MyClass


Does that make things any clearer?

AZ: comments to my example

I created a directory package_import and two enclosed directory testpackage and testpackage2.

Modified example with import a class from the current project (directory)
-------------------------------------------------------------------------

I added the file/class MyClassSamePackage.java in the package/directory of the main class TestPackageClass.java and imported it in the TestPackageClass.java.
NB: I changed NAME → name in the classes. 

package_import$ ls *
comment-AZ.t

testpackage:
MyClassSamePackage.class MyClassSamePackage.java  TestPackageClass.class   TestPackageClass.java

testpackage2:
MyClass.class MyClass.java

package_import$ cat testpackage/MyClassSamePackage.java
package testpackage;

public class MyClassSamePackage {
    public static String name = "testpackage.MyClassSamePackage";

    public static void main(String[] args) {
        MyClassSamePackage myClassSamePackage = new MyClassSamePackage();
        System.out.println("MyClassSamePackage main: " + name);
    }
}
package_import$ cat testpackage/TestPackageClass.java
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
package_import$ cat testpackage2/MyClass.java
package testpackage2;

public class MyClass {
    public static String name = "testpackage2.MyClass";
}

package_import$ javac testpackage/*.java
package_import$ javac testpackage2/*.java
package_import$ java testpackage.TestPackageClass
Hello from testpackage.TestPackageClass!
Now accessing testpackage.MyClassSamePackage
Now accessing testpackage2.MyClass
