import java.util.Scanner;

public class Age {
    public static void main(String[] args){
        int age;
        while (true) {
            Scanner sc = new Scanner(System.in);

            System.out.println("나이를 입력하세요.(0 입력시 종료)");
            age = sc.nextInt();

            if (age > 20) {
                System.out.println("성인");
                continue;
            }
            else if (age <= 20) {
                System.out.println("미성년자");
                continue;
            }
            sc.close();
            break;
        }
    }
}
