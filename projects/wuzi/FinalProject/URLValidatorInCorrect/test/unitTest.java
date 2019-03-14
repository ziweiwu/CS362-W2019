import junit.framework.TestCase;

public class unitTest extends TestCase {
  static final String[] schemes = {"http", "https", "ftp"};


  public void testIsValidPath() {
    UrlValidator urlVal = new UrlValidator(schemes, 0);

    String[] goodPathArray = {"/user", "/new", "/form", "/photo?"};
    String[] badPathArray = {"//", "///", "/../", "/.."};

    //assert for good path
    for (String path : goodPathArray) {
      System.out.println("Testing path " + path);
      assertTrue(urlVal.isValidPath(path));
    }

    //assert for bad path
    for (String path : badPathArray) {
      System.out.println("Testing path " + path);
      assertFalse(urlVal.isValidPath(path));
    }
  }


  public void testIsValidAuthority() {
    UrlValidator urlVal = new UrlValidator(schemes, 0);


    String[] badAuthorityArray = {"19216811", "www..google..com", "hello world", "1.1.1.1::80"};
    String[] goodAuthorityArray = {"www.google.com", "192.168.1.1", "www.facebook.com", "1.1.1.1:80"};

    //assert for bad authority
    for (String authority : badAuthorityArray) {
      System.out.println("Testing authority: " + authority);
      assertFalse(urlVal.isValidAuthority(authority));
    }

    //assert for good authority
    for (String authority : goodAuthorityArray) {
      System.out.println("Testing authority: " + authority);
      assertTrue(urlVal.isValidAuthority(authority));
    }
  }


  // Test isValidScheme()
  public void testIsValidScheme() {
    UrlValidator urlVal = new UrlValidator(schemes, 0);

    String[] goodSchemeArray = {"http", "https", "ftp"};
    String[] badSchemeArray = {"htp", "htttp", "", "fttp", "badttp", "badftp", "localhost"};


    //assert for good schemes
    for (String scheme : goodSchemeArray) {
      System.out.println("Testing scheme: " + scheme);
      assertTrue(urlVal.isValidScheme(scheme));
    }

    //assert for bad schemes
    for (String scheme : badSchemeArray) {
      System.out.println("Testing scheme: " + scheme);
      assertFalse(urlVal.isValidScheme(scheme));
    }
  }

  // Test isValid()
  public void testIsValid() {
    UrlValidator urlVal = new UrlValidator(schemes, 0);
    System.out.println("Unit Testing isValid()");

    String[] goodURLArray = {
            "http://www.google.com",
            "http://www.google.com/",
            "ftp://192.168.1/",
            "https://www.facebook.com"
    };

    String[] badURLArray = {
            "",
            "http:/www.google.com",
            "htttp://www.google.com",
            "http:/www.google..com",
            "ftp:/1.1.1.1:80",
    };

    // Assert for bad URLS
    for (String URL : badURLArray) {
      System.out.println("Testing URL: " + URL);
      assertFalse(urlVal.isValid(URL));
    }

    // Assert for good URLS
    for (String URL : goodURLArray) {
      System.out.println("Testing URL: " + URL);
      assertTrue(urlVal.isValid(URL));
    }
  }
}
