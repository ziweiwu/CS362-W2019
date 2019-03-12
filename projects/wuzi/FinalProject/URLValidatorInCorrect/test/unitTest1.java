import junit.framework.TestCase;

public class unitTest1 extends TestCase {

  public static void testIsValid() {
    String[] schemes = {"http", "https", "ftp"};
    UrlValidator urlVal = new UrlValidator(schemes, 0);
    System.out.println("Unit Testing isValid()");

    // assert for bad URLS
    assertFalse(urlVal.isValid(""));
    assertFalse(urlVal.isValid("http:\\www.google.com"));
    assertFalse(urlVal.isValid("htttp://www.google.com"));
    assertFalse(urlVal.isValid("http:/www.google.com"));
    assertFalse(urlVal.isValid("fttp:/www.google.com"));

    // assert for good URLS
    assertTrue(urlVal.isValid("http://www.google.com"));
    assertTrue(urlVal.isValid("http://www.google.com/"));
    assertTrue(urlVal.isValid("ftp://192.168.1/"));
  }

  public static void main(String[] args) {
    testIsValid();
  }
}
