#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LENGTH 50

struct Course {
    char className[MAX_LENGTH];
    char professorName[MAX_LENGTH];
    char classPlace[MAX_LENGTH];
    int grade;
};

void displayTimetable(struct Course* timetable, int hakjum);

int main() {
    struct Course* timetable = NULL;
    int timetableCreated = 0;
    int hakjum = 0;
    double grade = 0.0;
    double* goalGrade = &grade;

    while (1) {
        printf("\n\n대학생활 도우미 프로그램입니다.\n 무엇을 도와드릴까요?\n");
        printf("1. 시간표 관리\n2. 성적 관리\n3. 과제 관리\n4. 프로그램 종료\n");
        printf("-------------------------------------------------\n");
        printf("원하는 번호를 입력하세요.\n");

        int num = 0;
        scanf_s("%d", &num);

        if (num == 1) {
            if (!timetableCreated) {
                // 시간표를 입력받는 부분
                int grade = 0;
                int semester = 0;

                printf("시간표 관리 메뉴입니다.\n");
                printf("몇학년 몇학기 수업인가요? (띄어쓰기로 구분해서 학년,학기 작성)\n");
                scanf_s("%d %d", &grade, &semester);
                printf("총 몇개의 수업을 들으시나요?");
                scanf_s("%d", &hakjum);

                timetable = (struct Course*)malloc(hakjum * sizeof(struct Course));

                if (timetable == NULL) {
                    printf("메모리 할당 오류\n");
                    return -1;
                }

                printf("듣는 수업의 수업명, 교수명, 장소명을 차례대로 입력하세요. (띄어쓰기로 구분)\n");

                for (int i = 0; i < hakjum; i++) {
                    scanf_s("%49s %49s %49s", timetable[i].className, MAX_LENGTH, timetable[i].professorName, MAX_LENGTH, timetable[i].classPlace, MAX_LENGTH);
                }

                timetableCreated = 1; 
            }

            // 시간표 출력
            displayTimetable(timetable, hakjum);

            // 시간표 수정
            printf("\n1. 수업 추가\n2. 수업 삭제\n3. 이전으로\n");
            printf("원하는 번호를 입력하세요.\n");

            int option = 0;
            scanf_s("%d", &option);

            if (option == 1) {
                // 수업 추가
                    printf("추가할 수업의 수업명, 교수명, 장소명을 차례대로 입력하세요. (띄어쓰기로 구분)\n");
                    scanf_s("%s %s %s", timetable[hakjum].className, MAX_LENGTH, timetable[hakjum].professorName, MAX_LENGTH, timetable[hakjum].classPlace, MAX_LENGTH);
                    hakjum++;
                    printf("수업이 추가되었습니다.\n");
            }
            else if (option == 2) {
                // 수업 삭제
                if (hakjum > 0) {
                    printf("삭제할 수업의 번호를 입력하세요 (1부터 시작)\n");
                    int courseNumber = 0;
                    scanf_s("%d", &courseNumber);

                    if (courseNumber >= 1 && courseNumber <= hakjum) {
                        for (int i = courseNumber - 1; i < hakjum - 1; i++) {
                            timetable[i] = timetable[i + 1];
                        }
                        hakjum--;
                        printf("수업이 삭제되었습니다.\n");
                    }
                    else {
                        printf("잘못된 번호입니다.\n");
                    }
                }
                else {
                    printf("현재 수업이 없어 삭제할 수 없습니다.\n");
                }
            }
            else if (option == 3) {
                // 다시 메인메뉴 보이게 함
            }
            else {
                printf("잘못된 번호입니다.\n");
            }
        }

        else if (num == 2) {
            //성적 관리 프로그램 작성
            displayTimetable(timetable, hakjum);
            if (*goalGrade != 0.0) {
                printf("당신의 목표 성적은 %,2lf 입니다.\n\n", *goalGrade);
            }
            else {
                printf("아직 목표 성적이 입력되지 않았습니다.\n1번을 눌러 목표 성적을 입력하세요.\n");
            }

            int setGrade = 0;
            int option = 0;
            while (1) {
                printf("\n\n성적관리 프로그램\n---------------------\n");
                printf("1. 목표성적 입력 및 수정\n2. 각 수업 별 성적 입력 및 수정\n3. 이전으로\n");
                scanf_s("%d", &option);

                //목표 성적 입력 및 수정
                if (option == 1) {
                    if (!setGrade) { //목표 성적이 입력되어 있지 않은 경우
                        printf("목표 성적을 입력하세요: ");
                        scanf_s("%lf", goalGrade);
                        printf("당신의 목표 성적은 %.2lf 입니다.", *goalGrade);
                        setGrade = 1;
                    }
                    else { //목표 성적 수정
                        printf("수정할 목표 성적을 입력하세요.\n");
                        scanf_s("%lf", goalGrade);
                        printf("수정한 당신의 목표 성적은 %.2lf입니다.", *goalGrade);
                    }
                }

                //각 과목 별 목표 성적 입력 및 수정
                else if (option == 2) {

                }
                else if (option == 3) {
                    break;
                }
            }

		}
		else if (num == 3) {
			//과제 관리 프로그램 작성
		}
		else if (num == 4) { //프로그램 종료
            free(timetable);
            return 0;
		}

		else
			printf("잘못된 번호입니다. 다시 입력하세요\n\n");
	}

	return 0;
}

void displayTimetable(struct Course* timetable, int hakjum) {
    printf("\n시간표:\n-----------------------\n");
    for (int i = 0; i < hakjum; i++) {
        printf("%s | %s | %s\n", timetable[i].className, timetable[i].professorName, timetable[i].classPlace);
    }
}

