import junit.framework.TestCase;
import java.util.Random;


public class randomTest extends TestCase {

  public static void testIsValid() {
    String[] goodProtocol = {"http://", "https://", "ftp://"};
    String[] badProtocol = {"://", "https:/", "ftp"};
    
    String[] goodAuthority = {"www.google.com", "go.com", "0.0.0.0"};
    String[] badAuthority = {".1.2.3", "", "aaa"};
    
    String[] goodPort = {"", ":80", ":0"};
    String[] badPort = {":-1", "65a", "65636"};
    
    String[] goodPath = {"", "/test1/", "/t123"};
    String[] badPath = {"/..", "/..//file", "/test1//file"};
    
    String[] schemes = {"http", "https", "ftp"};
    UrlValidator urlVal = new UrlValidator(schemes, 0);
    Random rand = new Random();
    System.out.println("Random Testing isValid()");

    // assert for bad URLS: pick random indices but have at least one bad one in there
    
    // bad protocol
    String badString = badProtocol[rand.nextInt(3)] + goodAuthority[rand.nextInt(3)] 
    		+ goodPort[rand.nextInt(3)] + goodPath[rand.nextInt(3)];
    System.out.println("test bad URL " + badString);
    assertFalse(urlVal.isValid(badString));
    
    // bad authority
    badString = goodProtocol[rand.nextInt(3)] + badAuthority[rand.nextInt(3)] 
    		+ goodPort[rand.nextInt(3)] + goodPath[rand.nextInt(3)];
    System.out.println("test bad URL " + badString);
    assertFalse(urlVal.isValid(badString));
   
    // bad port
    badString = goodProtocol[rand.nextInt(3)] + goodAuthority[rand.nextInt(3)] 
    		+ badPort[rand.nextInt(3)] + goodPath[rand.nextInt(3)];
    System.out.println("test bad URL " + badString);
    assertFalse(urlVal.isValid(badString));
    
    // bad path
    badString = goodProtocol[rand.nextInt(3)] + goodAuthority[rand.nextInt(3)] 
    		+ goodPort[rand.nextInt(3)] + badPath[rand.nextInt(3)];
    System.out.println("test bad URL " + badString);
    assertFalse(urlVal.isValid(badString));
    
    // all bad
    badString = badProtocol[rand.nextInt(3)] + badAuthority[rand.nextInt(3)] 
    		+ badPort[rand.nextInt(3)] + badPath[rand.nextInt(3)];
    System.out.println("test bad URL " + badString);
    assertFalse(urlVal.isValid(badString));
    
    
    // assert for good URLS: pick randomly but only from good ones
    // use all good components, test many combinations
    for (int i = 0; i < 30; i++) {
	    String goodString = goodProtocol[rand.nextInt(3)] + goodAuthority[rand.nextInt(3)] 
	    		+ goodPort[rand.nextInt(3)] + goodPath[rand.nextInt(3)];
	    System.out.println("test good URL " + goodString);
	    assertTrue(urlVal.isValid(goodString));
    }
   
  }

  public static void main(String[] args) {
    testIsValid();
  }
}
