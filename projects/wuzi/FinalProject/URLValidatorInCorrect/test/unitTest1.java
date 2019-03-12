import junit.framework.TestCase;

public class unitTest1 extends TestCase {

  public static void testIsValid() {
    String[] schemes = {"http", "https"};
    UrlValidator urlVal = new UrlValidator(schemes, 0);
    System.out.println("Unit Testing isValid()");

    // assert for bad URLS
    assertFalse(urlVal.isValid(""));
    assertFalse(urlVal.isValid("http:\\www.google.com"));
    assertFalse(urlVal.isValid("htttp://www.google.com"));
    assertFalse(urlVal.isValid("http:/wwww.google.com"));
    assertFalse(urlVal.isValid("http:/wwww.googlecom"));

    // assert for good URLS
    assertTrue(urlVal.isValid("http://www.google.com"));
    assertTrue(urlVal.isValid("http://www.google.com/"));
  }

  public static void main(String[] args) {
    testIsValid();
  }
}
