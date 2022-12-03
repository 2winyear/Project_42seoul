import java.util.Scanner;

public class Gugudan {
    public static void main(String[] args){
        int gugu;

        while (true)
        {
            Scanner sc = new Scanner(System.in);
            
            System.out.println("구구단 출력(0 입력시 종료)");
            gugu = sc.nextInt();
            
            if (gugu == 0) break;
            for (int i = 1; i < 10; i++) {
                System.out.println(gugu + "*" + i + "=" + gugu * i);
            }
        }
    }
}
