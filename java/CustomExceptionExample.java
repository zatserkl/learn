// from https://coderanch.com/t/494597/java/find-Exception-thrown

public class CustomExceptionExample {
 
    public static void main(String[] args) {
        try {
            method1();
            method2();
        } catch (method1Exception ex) {
            System.out.println("Exception occured in method: 1");
        } catch (method2Exception ex) {
            System.out.println("Exception occured in method: 2");
        }
    }
 
    static void method1() throws method1Exception {
        try{
           new java.io.FileReader("some file doesn't exist !");
        } catch (java.io.IOException e){
            throw new method1Exception();
        }
    }
 
    static void method2() throws method2Exception {
        try {
            new java.io.FileReader("some file doesn't exist !");
        } catch (java.io.IOException e) {
            throw new method2Exception();
        }
    }
 
    static class method1Exception extends Exception{
        method1Exception(){
            super();
        }
    }
 
    static class method2Exception extends Exception{
        method2Exception(){
            super();
        }
    }
}
