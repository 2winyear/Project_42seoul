package unit05_except;

/* 
* Java 예외처리와 컬렉션 API 학습하기
* 
* Java 애플리케이션 개발에서 발생하는 예외(오류)를 처리하는 방법을 학습한다.
* Java 애플리케이션 개발에서 빈번하게 사용되는 컬렉션 API를 익히고 활용하는 방법를 학습한다.
* Java에서 제공하는 Exception 클래스의 계층과 Checked/UnChecked Exception을 구분하고 이해한다.
* 예외처리 문법인 try ~ catch 문과 메서드 선언에 사용되는 throws 문을 구분하고 이해한다.
* Java Collection API의 계층과 LIst 구조 & Map 구조를 이해하고 활용법을 학습한다.
* Collection API에서 많이 사용되는 Generic에 대해 이해하고 활용법을 학습한다.
* 반복문과 표준입력을 이용하여 도서명을 문자열로 입력받아 ArrayList에 저장한다.
* 반복문과 표준입력을 이용하여 도서명(Key)과 가격(Value)을 문자열로 입력받아 HashMap에 저장한다.
* 가격 저장 시 입력값이 숫자가 아닌 경우 try ~ catch를 이용하여 예외처리하고 다시 입력받도록 구현한다.
* 표준입력을 이용하여 ArrayList에 저장된 도서명을 검색하는 기능을 개발한다.
* 표준입력을 이용하여 HashMap에 저장된 도서명을 검색하는 기능을 개발한다.
* 표준입력을 이용하여 도서명을 검색하여 ArrayList/HashMap에 저장된 도서명을 삭제하는 기능을 개발한다.
* 삭제시 발생하는 예외는 try ~ catch를 이용하여 예외처리한다.
* 
* 개발환경에서 제공된 목록의 개발도구 중 선택하여 사용한다.
* Java Version은 8이상으로 사용한다.
* 각 기능은 main 메서드에 구현한다.
* 저장, 검색, 삭제, 종료 등의 기능은 메뉴화 하여 개발한다.
* 모든 식별자는(변수명, 클래스명, 메서드명 등) Java Naming Convention을 지키도록 한다.
* 표준입력은 System.in을 이용한다.
* Scanner를 이용하여 표준입력을 처리한다.
* 구현하는 모든 기능은 애플리케이션 사용자에게 프로그램 종료 여부를 묻고 종료를 원할 때 종료하도록 구현한다.
*/

import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.NoSuchElementException;

public class Demo {

    private static Scanner sc = new Scanner(System.in);
    private static BookCollection bookCollection = new BookCollection();

    public static void print_front() {
        System.out.println("-------------------------------------------------------------");
        System.out.println("---------------- 천하에 쓸데없는 도서관리 프로그램 ");
        System.out.println("----------------- Book Management Program -------------------");
        System.out.println("------------------- that NOWHERE TO USE ---------------------");
        System.out.println("------------------------------------------------------------");
        System.out.println();
    }
    
    public static String prompt_main() {
        
        System.out.println("  >>>> How to USE <<<<");
        System.out.println("  d\t delete Book");
        System.out.println("  e\t enroll new Book");
        System.out.println("  f\t find Book");
        System.out.println("  p\t print all Books");
        System.out.println("  q\t quit");
        String result = Demo.sc.nextLine();
        
        return result.toLowerCase();
    }
    
    public static void delete_title() {
        System.out.println("  삭제할 도셔명 입력");
        String title = Demo.sc.nextLine();
        bookCollection.remove(title);
    }

    public static boolean prompt_enroll() {
        int price;
        String title;
        StringTokenizer stk;

        System.out.println("  도셔명, 가격 입력(입력은, 로 구분하고 q 입력시 종료)");
        String result = Demo.sc.nextLine();
        
        try {
            stk = new StringTokenizer(result, ",");
            title = stk.nextToken();
            price = Integer.parseInt(stk.nextToken());
        } catch (NoSuchElementException e) {
            System.out.println("  Wrong Input");
            System.out.println();
            return false;
        }
        Demo.addBook(title, price);
        System.out.println("  -- new book added! --");
        System.out.println();

        return true;
    }

    public static void addBook(String title, int price) {
        bookCollection.add(title, price);
    }

    public static void print_askAgain() {
        System.out.println("  잘못된 입력. 다시 입력하세요.");
    }

    public static void find_book() {
        System.out.println("  찾고싶은 도셔명 입력");
        String title = Demo.sc.nextLine();
        if (bookCollection.find(title))
            System.out.println(title + "이(가) 있습니다.");
    }

    public static void print_bookList() {
        System.out.println("  -- List of Persons --");
        System.out.println(bookCollection.toString());
        bookCollection.printlist();
        System.out.println("  -- end of the list --");
        System.out.println();
    }
    
    public static void exit() {
        sc.close();
        System.out.println("  Bye!");
        System.exit(0);
    }
    public static void main(String[] args) {
        Demo.print_front();
        while (true) {
            switch (Demo.prompt_main()) {
                case "d":
                Demo.delete_title(); break;
                case "e":
                Demo.prompt_enroll(); break;
                case "f":
                Demo.find_book(); break;
                case "p":
                Demo.print_bookList(); break;
                case "q":
                Demo.exit();
                default:
                Demo.print_askAgain();
            }
        }
    }
}