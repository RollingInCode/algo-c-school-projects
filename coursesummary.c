//Franklyn Gonzalez
//COP3502 Computer Science I

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

#define MAXNAMESIZE 20

typedef struct student{
    int id;
    char *lname; //stores last name of student
    float *scores; //stores scores of the student. Size is taken from num_scores array.
    float std_avg; //average score of the student (to be calculated)
} student;

typedef struct course{
    char *course_name; //stores course name
    int num_sections; //number of sections
    student **sections;//stores array of student arrays(2D array). Size is num_sections;
    int *num_students;//stores array of number of students in each section. Size is num_sections;
    int *num_scores; //stores array of number of assignments in each section. Size is num_sections;
} course;

//function calls
//void release_courses(course *courses, int num_courses); //this is to free
void process_courses(course *course, int num_courses); //this is to process
student** read_sections(int num_students[], int num_scores[], int num_sections);
course* read_course(int *num_courses);



int main (void) {
    //atexit(report_mem_leak);

    int testcase, numCourses, numSections, numStudents, numAssignments, numScores;

    int pass_count = 0;

    //test case (num of)
    scanf("%d", &testcase); ///number of test cases

    for (int i = 0; i<testcase; i++) { //num of testcases

        //number of courses
        scanf("%d", &numCourses);
        //allocate the number of courses
        course* allCourses = malloc(numCourses*sizeof(course));

            // num of courses

            allCourses = read_course(&numCourses);//read course information

            release_courses(&allCourses[i], numCourses);//free memory for courses


    return 0;
}

//void release_courses(course *courses, int num_courses) {
//
//}

void process_courses(course *course, int num_courses) {

    float sum = 0;

    student* std_avg = malloc(numStudents*sizeof(int));
    student* scores = malloc(numStudents*sizeof(float));
    int *averageScore = malloc(numStudents*sizeof(int));


    for (int i = 0;i<num_courses;i++) {
        sum = sum + student.scores[i];
    }
    for (int i = 0;i<numStudents;i++) {
        averageScore[i] = (double) (sum/numStudents);
        if (averageScore[i] > 70) {
            pass_count++;
        }
    }

}

student** read_sections(int num_students[], int num_scores[], int num_sections) {
    course* sections = calloc(num_sections, sizeof(course)); // allocate memory for Sections
    course* numStudents = malloc(num_sections*sizeof(int)); // allocate memory for students
    scanf("%d", &numStudents); //input for students
    course* numScores = malloc(numAssignments*sizeof(float)); // allocate memory for scores
    student* id = malloc(numStudents*sizeof(int));
    student* lname = malloc(MAXNAMESIZE+1*sizeof(char));

    student **sections = malloc(num_sections*sizeof(student*));



    for (int i=0;i<numStudents;i++) {
        scanf("%d", &student.id);
        scanf("%s", student.lname);
        for (int j = 0;j<numAssignments;i++) {
        scanf("%.1f", numScores); //input score
        }
        process_courses(numScores,numCourses);
        for (int j = 0l j < num_students[i]; j++){
            scanf("%d",sections[i][j].id);
            scanf("%s",sections[i][j].lname);
        }
    }

}

course* read_course(int *num_courses) {
        int numCourses = *num_courses;


        course* allCourses = malloc(numCourses*sizeof(course));

        for (int i=0;i<num_courses;i++) {
            char tmp[MAXNAMESIZE+1];
            scanf("%s", tmp);
            int len = strlen(tmp);
            allCourses[i].course_name = calloc(len+1, sizeof(char)); // allocate memory for Course_name
            strcpy(allCourses[i].course_name, tmp);

            //number of Sections

            scanf("%d", &allCourses[i].num_sections);
            printf("%d", allCourses[i].num_sections);
            student* sections = malloc(numCourses*sizeof(student));

            int *sectionsOfStudents = malloc(allCourses[i].num_sections * sizeof(int *));

            for (int j =0; i<allCourses[i].num_sections; i++){
                scanf("%d", &allCourses[j].num_students);
                sectionsOfStudents[j] = malloc(numStudents * sizeof(int));

            }


            for (int k = 0;i<num_courses;i++) {
                allCourses[k].sections = read_sections(allCourses[k].num_students, allCourses[k].num_scores, allCourses[k].num_sections);
                //allCourses[k].num_students = calloc(numStudents, sizeof(course));
            }


        }
        return allCourses;

}


