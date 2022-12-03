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

import java.util.ArrayList;
import java.util.HashMap;

public class BookCollection {
    private int count = 0;
    private ArrayList<String> list = new ArrayList<>();
    private HashMap<String, Integer> map = new HashMap<>();

	public BookCollection() {
		this.printLog("  ...Creating new BookCollection Object");
	}

	public boolean add(String title, int price) {
		if (this.find(title) == true) {
			this.printLog("  -- Add Failure: existing Title.");
			return false;
		}
		this.list.add(title);
		this.map.put(title, price);
		this.count++;

		this.printLog("  -- added.");

		return true;
	}

	public boolean remove(String title) {
		if (this.find(title) == false) {
			this.printLog("  -- Error: parameter doesn't exist.");
			return false;
		}
		this.list.remove(title);
		this.map.remove(title);
		this.count--;

		this.printLog("  -- removed.");

		return true;
	}

	public boolean find(String title) {
		return this.map.containsKey(title);
	}

	public int priceOf(String title) {
		if (this.find(title) == false) {
			this.printLog("  -- Error: parameter doesn't exist.");
			return -1;
		}
		return this.map.get(title).intValue();
	}

	public boolean modify(String title, String newTitle, int price) {
		if (this.find(title) == false) {
			this.printLog("  -- Error: parameter doesn't exist.");
			return false;
		}
		if (title == newTitle) {
			this.map.replace(newTitle, price);
		} else {
			int index = this.list.indexOf(title);
			this.list.set(index, newTitle);
			this.map.remove(title);
			this.map.put(newTitle, price);
		}
		return true;
	}

    public String toString() {
        return
        "[ BookCollection ] " +
        ", Total Count of Books: " + this.count;
    }

	public void printlist() {
		for (String title: list) {
			System.out.println("책제목: " + title);
		}
	}

	private void printLog(String... str) {
		System.out.println(str);
	}

    public int getCount() { return this.count; }
}
