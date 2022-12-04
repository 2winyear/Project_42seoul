import java.util.Scanner;

public class Sum {
    public static void main(String[] args){
        int num;
        int sum = 0;

        System.out.println("합계를 구할 숫자를 입력하세요.(0 입력시 종료)");

        while (true)
        {
            Scanner sc = new Scanner(System.in);

            System.out.print(">> ");
            num = sc.nextInt();

            if(num == 0) break;
            sum += num;
        }
        System.out.println("합계는 " + sum + "입니다.");
    }
}
