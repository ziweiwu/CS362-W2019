import junit.framework.TestCase;
import java.util.Random;


public class randomTest extends TestCase {

  public static void testIsValid() {
	// create both good and bad arrays of the different URL parts to mix and match randomly
    String[] goodProtocol = {"http://", "https://", "ftp://", "h3t://", ""};
    String[] badProtocol = {"://", "https:/", "ftp:", "3ht://"};
    
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
    for (int i = 0; i < 5; i++) {
	    String badString = badProtocol[rand.nextInt(4)] + goodAuthority[rand.nextInt(3)] 
	    		+ goodPort[rand.nextInt(3)] + goodPath[rand.nextInt(3)];
	    System.out.println("test bad URL " + badString);
	    assertFalse(urlVal.isValid(badString));
    }
    
    // bad authority
    for (int i = 0; i < 5; i++) {
	    String badString = goodProtocol[rand.nextInt(5)] + badAuthority[rand.nextInt(3)] 
	    		+ goodPort[rand.nextInt(3)] + goodPath[rand.nextInt(3)];
	    System.out.println("test bad URL " + badString);
	    assertFalse(urlVal.isValid(badString));
    }
   
    // bad port
    for (int i = 0; i < 5; i++) {
	    String badString = goodProtocol[rand.nextInt(5)] + goodAuthority[rand.nextInt(3)] 
	    		+ badPort[rand.nextInt(3)] + goodPath[rand.nextInt(3)];
	    System.out.println("test bad URL " + badString);
	    assertFalse(urlVal.isValid(badString));
    }
    
    // bad path
    for (int i = 0; i < 5; i++) {
	    String badString = goodProtocol[rand.nextInt(5)] + goodAuthority[rand.nextInt(3)] 
	    		+ goodPort[rand.nextInt(3)] + badPath[rand.nextInt(3)];
	    System.out.println("test bad URL " + badString);
	    assertFalse(urlVal.isValid(badString));
    }
    
    // all bad
    for (int i = 0; i < 5; i++) {
	    String badString = badProtocol[rand.nextInt(4)] + badAuthority[rand.nextInt(3)] 
	    		+ badPort[rand.nextInt(3)] + badPath[rand.nextInt(3)];
	    System.out.println("test bad URL " + badString);
	    assertFalse(urlVal.isValid(badString));
    }
    
    
    // assert for good URLS: pick randomly but only from the good arrays
    
    // use all good components, test many combinations
    for (int i = 0; i < 30; i++) {
	    String goodString = goodProtocol[rand.nextInt(5)] + goodAuthority[rand.nextInt(3)] 
	    		+ goodPort[rand.nextInt(3)] + goodPath[rand.nextInt(3)];
	    System.out.println("test good URL " + goodString);
	    assertTrue(urlVal.isValid(goodString));
    }
   
  }

  public static void main(String[] args) {
    testIsValid();
  }
}
