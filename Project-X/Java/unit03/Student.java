import java.util.Scanner;
import java.util.StringTokenizer;

public class Student {
    private int studentId;
    private String name;
    private String major;

    public String getName() {
        return this.name;
    }
    
    public int getStudentId() {
        return this.studentId;
    }
    
    public String getMajor() {
        return this.major;
    }
    
    public void setName(String name) {
        this.name = name;
    }
    
    public void setStudentId(int id) {
        this.studentId = id;
    }
    
    public void setMajor(String major) {
        this.major = major;
    }

    public String toString() {
        return "name: " + this.name +
            "studentId" + this.studentId +
            "major" + this.major;
    }
    public static void main(String[] args) {
        Student[] StudentList = new Student[10];
        int i = 0;

        while (true)
        {
            System.out.println("이름,학번,학과 입력(입력은, 로 구분하고 x 입력시 종료)");
            Scanner sc = new Scanner(System.in);
            String text = sc.nextLine();
            if (text.toLowerCase().equals("x")) break;
            
            StringTokenizer stk = new StringTokenizer(text, ",");
            
            StudentList[i] = new Student();
            StudentList[i].setName(stk.nextToken());
            StudentList[i].setStudentId(Integer.parseInt(stk.nextToken()));
            StudentList[i].setMajor(stk.nextToken());
            System.out.println(StudentList[i].toString());
            
            i++;
            if (i == 10) {
                System.out.println("학생이 꽉 찼습니다.");
                // 출력
            }
        }
    }
}