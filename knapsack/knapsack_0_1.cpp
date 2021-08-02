#include <iostream>
#include <math.h>
#include <array>
#include <iomanip> //for setw(n)
using namespace std;

//Program written by Jalaluddin Qureshi, 17/July/2021.
//The objective of this program is to code the algorithm for the 0-1 Knapsack Problem.

//A formal description of the problem, and the solution can be found in the following book.
//Kleinberg, Jon, and Eva Tardos. Algorithm design. Pearson Education India, 2006. (Chapter 6 on Dynamic Programming).

//Input taken: Weights of n objects, and W the maximum capacity of the container.
//Output-1: Optimal (maximum) value of the total weights which can fit inside the container.
//Output-2: The objects which are used to achieve the optimal.

//weights of the items.
//Assumption: The weights are sorted in increasing order.
//If items is unsorted, then one of the well-known sorting algorithms can be used
//to sort the list in O(n log n) time complexity;
int const items[] = {1, 2, 10, 11, 14, 14};//{1, 1, 3, 3, 4, 5, 6, 11, 14, 14};
int const max_weight = 13;

int const item_len = sizeof(items)/sizeof(items[0]);

//those objects with weights greater than max_weight would be excluded later.
//The value of items_max would be found using search_index(int, int) function.
int items_max = item_len;

//after calling the search_index(int, int) function, the first array index
//will run/ loop/ store values until items_max, where items_max<=items[].size()
int opt_table[item_len][max_weight+1];

//stores the list of items which have been selected.
int index_0_1[item_len];

//Uses a recursive Binary Search.
//Searches for the number of items whose weight is less than or equal to max_weight.
//For those items whose weight is greater than the max_weight, they are excluded from
//further analysis. This minimizes the computational time of running the a algorithm
//which has a complexity of O(nW), where n is the number of items and W is the total
//weight.
int search_index(int head, int tail) {
    int array_size = tail-head;

    int mid_point = floor(double(array_size)/2) + head;
    //cout << head << " " << tail << endl;

    //base condition.
    //Note: in the return statement the number of items is being returned,
    //and not any array index.
    if (array_size==1) {
        return head;
    }
    //binary search for a value which is greater than the max_weight value
    //the interval [head, tail) contains the number larger than the max_weight.
    else if (items[mid_point-1]<=max_weight) {
        return search_index(mid_point, tail);
    }
    else {
        return search_index(head, mid_point);
    }

}

//initialization of the opt_table. All the elements in the first
//row are assigned a value equal to zero.
void initialize_opt_table() {
    for (int j=0; j<=max_weight; j++) {
        opt_table[0][j] = 0;
    }
}

//called by the compute_Miw function.
int compute_opt(int i, int w) {

    //base condition
    if (i==0) {
        return 0; //essentially this statement is returning opt_table[0][w]
    }

    int opt_1 = opt_table[i-1][w];
    int opt_2 = w-items[i]>=0 ? items[i] + opt_table[i-1][w-items[i]] : -1;

    //if opt_2 is undefined
    if (opt_2==-1) {
        return opt_1;
    }
    //else returns the maximum of opt_1, opt_2.
    else {
        return opt_1>opt_2 ? opt_1 : opt_2;
    }
}

//compute the tabular value of the 2-d array with index i and w.
void compute_Miw() {
    for (int i=1; i<items_max; i++) {
        for (int w=0; w<=max_weight; w++) {
            opt_table[i][w] = compute_opt(i, w);
        }
    }
}

//determines the list of items which have been selected as part
//of the optimal solution. Selected items are assigned a value of 1.
void items_index() {
    int w = opt_table[items_max-1][max_weight];

    for (int i=items_max-1; (i>0) && (w>0); i--) {
        if (opt_table[i][w]>opt_table[i-1][w]) {
            index_0_1[i] = 1;
            w -= items[i];
        }
    }
}

//initializes the 0_1 vector.
void initialize_index() {
    for (int i=1; i<items_max; i++) {
        index_0_1[i]=0;
    }
}

//prints the opt_table.
void display_table() {

    for (int i=0; i<items_max; i++) {
        for (int w=0; w<=max_weight; w++) {
            cout << setw(3) << opt_table[i][w] << " ";
        }
        cout << endl;
    }
}

//displays the list of items which have been selected, their
//corresponding weight, and the total number of items, and the
//total weight of all the items.
void display_items_selected() {

    cout << setw(7) << "Item Id" << setw(10) << "Item Wgt" << endl;

    int tot_items = 0, tot_weight=0;
    for (int i=0; i<items_max; i++) {
        if (index_0_1[i]==1) {
            cout << setw(7) << i << setw(10) << items[i] << endl;
            tot_items++;
            tot_weight +=items[i];
        }
    }
    cout << setw(7) << "***" << setw(10) << "***" << endl;
    cout << "Sum " << setw(3) << tot_items << setw(10) << tot_weight << endl;

}


int main() {

    //First step is to only consider those items whose weight is less than or equal to the max_weight.
    //if there is an item with weight equal to max_weight then only that item is selected, and the search
    //terminates without running any additional steps.
    bool solution_found = false;

    //this if statement is executed if and only if the value of the last item is greater than
    //the max_weight.
    if (items[item_len-1]>max_weight) {
        items_max = search_index(0, item_len);
    }

    cout << "tot_items " << items_max << endl;

    //if there is an object whose weight is exactly equal to the max_weight, then this object
    //can be used to optimally solve the problem without running the Knapsack algorithm.
    if (items[items_max-1]==max_weight) {
        solution_found = true;
    }

    if (solution_found==false) {

        initialize_opt_table();

        compute_Miw();

        //initializes the 0_1 vector array.
        initialize_index();

        //identifies the items which have been selected to reach the optimal.
        items_index();

        //displays the list of items and their weights which have been selected.
        display_items_selected();
    }

    else {
        cout << "There exist an object with exact weight " << max_weight << " which can be used to solve the problem!";
    }

    return 0;
}
