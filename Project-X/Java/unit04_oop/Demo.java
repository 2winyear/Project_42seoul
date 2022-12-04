/* 
 * Java 객체지향개념 학습하기
 * 
 * 상속과 다형성 등 Java 객체지향(OOP, Object Oriednted Programming) 프로그래밍 개념과 적용방법을 학습한다.
 * - 이름, 나이를 멤버 변수로 가지는 Person 클래스를 개발한다.
 * - Person 클래스에 기본생성자를 포함한 Setter/Getter/toString 메서드를 개발한다.
 * - Person 클래스에 doSomething() 메서드를 정의한다.
 * - work 메서드를 가지는 Worker 인터페이스를 정의한다.
 * - Person 클래스의 자식클래스로 사번을 추가로 저장하는 Employee 클래스를 개발한다.
 * - Employee 클래스는 Worker 인터페이스를 구현한다.
 * - Employee 클래스에 기본생성자를 포함한 Setter/Getter/toString 메서드를 개발한다.
 * - Person 클래스에서 정의한 doSomething 메서드를 오버라이딩한다.
 * - Peron 클래스와 Employee 클래스를 이용하여 각각 객체를 생성한다.
 * - 생성된 객체를 배열에 저장한다.
 * - 반복문을 이용하여 배열에 저장된 객체의 정보를 toString 메서드를 이용하여 출력한다.
 * - 반복문을 이용하여 배열에 저장된 객체의 doSomething 메서드를 호출한다.
 * - 반복문을 이용하여 배열에 저장된 객체가 Worker 타입인 경우 work 메서드를 호출한다.
 * 
 * 개발환경에서 제공된 목록의 개발도구 중 선택하여 사용한다.
 * Java Version은 8이상으로 사용한다.
 * Person 클래스의 멤버 변수는 이름, 나이 이다
 * Employee 클래스가 추가로 저장할 멤버 변수는 사번 이다.
 * doSomething, work 메서드는 Console 출력하도록 구현한다.
 * 모든 식별자는(변수명, 클래스명, 메서드명 등) Java Naming Convention을 지키도록 한다.
 * 표준입력은 System.in을 이용한다.
 * Scanner를 이용하여 표준입력을 처리한다.
 * 구현하는 모든 기능은 애플리케이션 사용자에게 프로그램 종료 여부를 묻고 원할 때 종료하도록 구현한다.
 *
 */

package unit04_oop;

import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.NoSuchElementException;

public class Demo {

    private static final Person[] persons = new Person[10];
    private static int currentIndex = 0;
    private static Scanner sc = new Scanner(System.in);

    public static void print_front() {
        System.out.println("------------------------------------------------------------");
        System.out.println("---------------- 천하에 쓸데없는 학생관리 프로그램 ");
        System.out.println("--------------- Student Management Program -----------------");
        System.out.println("------------------ that NOWHERE TO USE ---------------------");
        System.out.println("------------------------------------------------------------");
        System.out.println();
    }

    public static String prompt_main() {

        System.out.println("  >>>> How to USE <<<<");
        System.out.println("  e\t enroll new Persons");
        System.out.println("  p\t print all Persons");
        System.out.println("  q\t quit");
        String result = Demo.sc.nextLine();
    
        return result.toLowerCase();
    }

    public static boolean prompt_enroll() {
        int age;
        String name;
        StringTokenizer stk;

        if (Demo.currentIndex == 10) {
            System.out.println("  List is FULL");
            return false;
        }

        System.out.println("  이름,나이 입력(입력은, 로 구분하고 q 입력시 종료)");
        String result = Demo.sc.nextLine();
        try {
            stk = new StringTokenizer(result, ",");
            name = stk.nextToken();
            age = Integer.parseInt(stk.nextToken().strip());
        } catch (NoSuchElementException e) {
            System.out.println("  Wrong Input");
            System.out.println();
            return false;
        }
        System.out.println("  추가 사번 입력");
        String num = Demo.sc.nextLine().strip();
        if (num.isEmpty()) {
            Demo.enrollPerson(name, age);
            System.out.println("  -- new person added! --");
        }
        else {
            Demo.addEmployNum(Integer.parseInt(num), name, age);
            System.out.println("  -- new employee added! --");
        }
        System.out.println();

        return true;
    }

    public static boolean addEmployNum(int num, String name, int age) {
        Demo.persons[Demo.currentIndex] = new Employee(num, name, age, Person.Status.UND);
        Demo.currentIndex++;

        return true;
    }

    public static boolean enrollPerson(String name, int age) {
        Demo.persons[Demo.currentIndex] = new Person(name, age, Person.Status.UND);
        Demo.currentIndex++;
        
        return true;
    }

    public static void print_personList() {
        System.out.println("  -- List of Persons --");
        for (int idx = 0; idx < Demo.currentIndex; idx++) {
            Person person = Demo.persons[idx];
            System.out.println(person.toString());
            if (person.getClass() == Employee.class) {
                ((Employee)person).work();
            } else {
                person.doSomething();
            }
        }
        System.out.println("  -- end of the list --");
        System.out.println();
    }


    public static void print_askAgain() {
        System.out.println("  잘못된 입력. 다시 입력하세요.");
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
                case "e":
                Demo.prompt_enroll(); break;
                case "p":
                Demo.print_personList(); break;
                case "q":
                Demo.exit();
                default:
                Demo.print_askAgain();
            }
        }
    }
}