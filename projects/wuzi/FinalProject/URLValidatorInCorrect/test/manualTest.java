import java.util.Scanner;

/*
 * The function allows user performs manual testing for isValid()
 */
public class manualTest {
  public static void manualTestFunc() {
    String URL;
    Scanner scan = new Scanner(System.in);

    // Intialize a URL validator
    String[] schemes = {"http", "https", "ftp"};
    UrlValidator urlVal = new UrlValidator(schemes, 0);

    // Keep asking user to input an URL to check if it's valid
    System.out.println("This program examines if an URL is valid, enter `Q` to exit the loop");
    do {
      System.out.print("Please enter a URL: ");
      URL = scan.next(); // get user input
      if (urlVal.isValid(URL)) {
        System.out.print("Valid\n\n");
      } else {
        System.out.print("Invalid\n\n");
      }
    } while (URL.equals("Q") == false);
  }

  public static void main(String[] args) {
    manualTestFunc();
  }
}

