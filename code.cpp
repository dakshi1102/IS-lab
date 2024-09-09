#include <bits/stdc++.h> 
 
using namespace std; 
 
int seek_count_fcfs; 
int seek_count_sstf; 
int seek_count_scan; 
int seek_count_cscan; 
int seek_count_look; 
int seek_count_clook; 
 
int size = 8; 
 
// FCFS 
void FCFS(int arr[], int head) 
{ 
    int seek_count = 0; 
    int distance, cur_track; 
 
    for (int i = 0; i < size; i++) 
    { 
        cur_track = arr[i]; 
 
        distance = abs(cur_track - head); 
        seek_count += distance; 
        head = cur_track; 
    } 
    seek_count_fcfs = seek_count; 
 
    cout << "Total number of seek operations = " << seek_count << endl; 
 
    cout << "Seek Sequence is" << endl; 
 
    for (int i = 0; i < size; i++) 
    { 
        cout << arr[i] << endl; 
    } 
} 
 
// SSTF 
void calculatedifference(int request[], int head, int diff[][2], int n) 
{ 
    for (int i = 0; i < n; i++) 
    { 
        diff[i][0] = abs(head - request[i]); // find difference of all the track 
time from head & store in a 2-d array. 
    } 
} 
 
int findMIN(int diff[][2], int n) 
{ 
    int index = -1; // Index of the track which has the minimum difference from the 
head. 
    int minimum = INT_MAX; 
 
    for (int i = 0; i < n; i++) 
    { 
        if (!diff[i][1] && minimum > diff[i][0]) // condition to check if the track 
is not visited and the minimum is not greater than current track. 
        { 
            minimum = diff[i][0]; 
            index = i; 
        } 
    } 
    return index; 
} 
 
void shortestSeekTimeFirst(int request[], int head, int n) 
{ 
    if (n == 0) // If array(request array) is zero, return nothing. 
    { 
        return; 
    } 
 
    int diff[n][2] = {{0, 0}}; // array to store the difference. 
    int seekcount = 0; 
    int seeksequence[n + 1] = {0}; 
 
    for (int i = 0; i < n; i++) 
    { 
        seeksequence[i] = head; 
        calculatedifference(request, head, diff, n); 
        int index = findMIN(diff, n); 
        diff[index][1] = 1; // mark the visited tracks. 
 
        seekcount += diff[index][0]; 
        head = request[index]; 
    } 
    seeksequence[n] = head; 
 
    seek_count_sstf = seekcount; 
 
    cout << "Total number of seek operations = " 
         << seekcount << endl; 
    cout << "Seek sequence is : " 
         << "\n"; 
 
    for (int i = 0; i <= n; i++) 
    { 
        cout << seeksequence[i] << "\n"; 
    } 
} 
 
// SCAN 
int disk_size = 200; 
 
void SCAN(int arr[], int head, string direction) 
{ 
    int seek_count = 0; 
    int distance, cur_track; 
    vector<int> left, right; 
    vector<int> seek_sequence; 
 
    if (direction == "left") 
        left.push_back(0); 
    else if (direction == "right") 
        right.push_back(disk_size - 1); 
 
    for (int i = 0; i < size; i++) 
    { 
        if (arr[i] < head) // push the elements which are less than the head to the 
left vector. 
            left.push_back(arr[i]); 
        if (arr[i] > head) // push the elements which are greater than the head to 
the right of the vector. 
            right.push_back(arr[i]); 
    } 
 
    std::sort(left.begin(), left.end()); 
    std::sort(right.begin(), right.end()); 
 
    int run = 2; // counter for the left and right direction. 
    while (run--) 
    { 
        if (direction == "left") 
        { 
            for (int i = left.size() - 1; i >= 0; i--) 
            { 
                cur_track = left[i]; 
 
                seek_sequence.push_back(cur_track); 
                distance = abs(cur_track - head); 
                seek_count += distance; 
                head = cur_track; 
            } 
            direction = "right"; 
        } 
        else if (direction == "right") 
        { 
            for (int i = 0; i < right.size(); i++) 
            { 
                cur_track = right[i]; 
                seek_sequence.push_back(cur_track); 
                distance = abs(cur_track - head); 
                seek_count += distance; 
                head = cur_track; 
            } 
            direction = "left"; 
        } 
    } 
 
    seek_count_scan = seek_count; 
 
    cout << "Total number of seek operations = " << seek_count << endl; 
 
    cout << "Seek Sequence is" << endl; 
 
    for (int i = 0; i < seek_sequence.size(); i++) 
    { 
        cout << seek_sequence[i] << endl; 
    } 
} 
 
// C-SCAN 
void CSCAN(int arr[], int head) 
{ 
    int seek_count = 0; 
    int distance, cur_track; 
    vector<int> left, right; 
    vector<int> seek_sequence; 
 
    left.push_back(0);              // 0 
    right.push_back(disk_size - 1); // 199 
 
    for (int i = 0; i < size; i++) 
    { 
        if (arr[i] < head) 
            left.push_back(arr[i]); 
        if (arr[i] > head) 
            right.push_back(arr[i]); 
    } 
 
    std::sort(left.begin(), left.end()); 
    std::sort(right.begin(), right.end()); 
 
    for (int i = 0; i < right.size(); i++) 
    { 
        cur_track = right[i]; 
        seek_sequence.push_back(cur_track); 
        distance = abs(cur_track - head); 
        seek_count += distance; 
        head = cur_track; 
    } 
    head = 0; 
    seek_count += (disk_size - 1); // goes to the last element of the disc 
size(199) 
 
    for (int i = 0; i < left.size(); i++) 
    { 
        cur_track = left[i]; 
        seek_sequence.push_back(cur_track); 
        distance = abs(cur_track - head); 
        seek_count += distance; 
        head = cur_track; 
    } 
 
    seek_count_cscan = seek_count; 
 
    cout << "Total number of seek operations = " << seek_count << endl; 
 
    cout << "Seek Sequence is" << endl; 
 
    for (int i = 0; i < seek_sequence.size(); i++) 
    { 
        cout << seek_sequence[i] << endl; 
    } 
} 
 
// LOOK 
void LOOK_DISC(int arr[], int head, string direction) 
{ 
    int seek_count = 0; 
    int distance, cur_track; 
    vector<int> left, right; 
    vector<int> seek_sequence; 
 
    for (int i = 0; i < size; i++) 
    { 
        if (arr[i] < head) 
            left.push_back(arr[i]); 
        if (arr[i] > head) 
            right.push_back(arr[i]); 
    } 
 
    std::sort(left.begin(), left.end()); 
    std::sort(right.begin(), right.end()); 
 
    int run = 2; 
    while (run--) 
    { 
        if (direction == "left") 
        { 
            for (int i = left.size() - 1; i >= 0; i--) 
            { 
                cur_track = left[i]; 
                seek_sequence.push_back(cur_track); 
                distance = abs(cur_track - head); 
                seek_count += distance; 
                head = cur_track; 
            } 
            direction = "right"; 
        } 
        else if (direction == "right") 
        { 
            for (int i = 0; i < right.size(); i++) 
            { 
                cur_track = right[i]; 
                seek_sequence.push_back(cur_track); 
                distance = abs(cur_track - head); 
                seek_count += distance; 
                head = cur_track; 
            } 
            direction = "left"; 
        } 
    } 
 
    seek_count_look = seek_count; 
 
    cout << "Total number of seek operations = " 
         << seek_count << endl; 
 
    cout << "Seek Sequence is" << endl; 
 
    for (int i = 0; i < seek_sequence.size(); i++) 
    { 
        cout << seek_sequence[i] << endl; 
    } 
} 
 
// CLOOK 
void CLOOK(int arr[], int head) 
{ 
    int seek_count = 0; 
    int distance, cur_track; 
    vector<int> left, right; 
    vector<int> seek_sequence; 
 
    for (int i = 0; i < size; i++) 
    { 
        if (arr[i] < head) 
            left.push_back(arr[i]); 
        if (arr[i] > head) 
            right.push_back(arr[i]); 
    } 
 
    std::sort(left.begin(), left.end()); 
    std::sort(right.begin(), right.end()); 
 
    for (int i = 0; i < right.size(); i++) 
    { 
        cur_track = right[i]; 
        seek_sequence.push_back(cur_track); 
        distance = abs(cur_track - head); 
        seek_count += distance; 
        head = cur_track; 
    } 
    seek_count += abs(head - left[0]); 
    head = left[0]; // make the first track of the disc as head and then goes to 
the right from there. 
 
    for (int i = 0; i < left.size(); i++) 
    { 
        cur_track = left[i]; 
        seek_sequence.push_back(cur_track); 
        distance = abs(cur_track - head); 
        seek_count += distance; 
        head = cur_track; 
    } 
 
    seek_count_clook = seek_count; 
 
    cout << "Total number of seek operations = " 
         << seek_count << endl; 
 
    cout << "Seek Sequence is" << endl; 
 
    for (int i = 0; i < seek_sequence.size(); i++) 
    { 
        cout << seek_sequence[i] << endl; 
    } 
} 
 
void compare() 
{ 
 
    cout << "\nCOMPARISON OF DIFFERENT ALGORITHMS ON THE BASIS OF SEEK COUNT:"; 
    cout << "\nFCFS: " << seek_count_fcfs; 
    cout << "\nSSTF: " << seek_count_sstf; 
    cout << "\nSCAN: " << seek_count_scan; 
    cout << "\nCSCAN: " << seek_count_cscan; 
    cout << "\nLOOK: " << seek_count_look; 
    cout << "\nCLOOK: " << seek_count_clook; 
 
    int arr[6] = {seek_count_fcfs, seek_count_sstf, seek_count_scan, 
seek_count_cscan, seek_count_look, seek_count_clook}; 
    sort(arr, arr + 6); 
    cout << "\nMinimum seek time: " << arr[0] << endl; 
    if (arr[0] == seek_count_fcfs) 
    { 
        cout << "FCFS IS THE BEST ALGORITHM"; 
    } 
    else if (arr[0] == seek_count_sstf) 
    { 
        cout << "SSTF IS THE BEST ALGORITHM"; 
    } 
    else if (arr[0] == seek_count_scan) 
    { 
        cout << "SCAN IS THE BEST ALGORITHM"; 
    } 
    else if (arr[0] == seek_count_cscan) 
    { 
        cout << "C-SCAN IS THE BEST ALGORITHM"; 
    } 
    else if (arr[0] == seek_count_look) 
    { 
        cout << "LOOK IS THE BEST ALGORITHM"; 
    } 
    else if (arr[0] == seek_count_clook) 
    { 
        cout << "C-LOOK IS THE BEST ALGORITHM"; 
    } 
} 
 
int main() 
{ 
 
    cout << 
"\n********************************************************************************
 **********************\n"; 
    cout << "\t\t\t\t\t1.Mehak Mathur-20103065\n\t\t\t\t\t2.Rahul Raina
20103082\n\t\t\t\t\t3.Ishaan Verma-20103086\n"; 
    int arr[size] = {105, 81, 37, 65, 92, 108, 41, 210}; 
    cout << "\t\t\t\tComparitive Analysis of Disc Scheduling Algorithm\n"; 
    int head = 50; 
label: 
 
    cout << 
"\n********************************************************************************
 **********************\n"; 
 
    cout << "\nMENU\n"; 
    cout << "1. FCFS\n2.SSTF\n3.SCAN\n4.C-SCAN\n5.LOOK\n6.C-LOOK\n7.Compare all 
scheduling\n8.Exit\n"; 
    int val; 
    cout << "Enter Choice:"; 
    cin >> val; 
 
    if (val == 1) 
    { 
        cout << "\nFCFS Disk Scheduling Algorithm :" << endl; 
        FCFS(arr, head); 
        cout << "\n" 
             << endl; 
        goto label; 
    } 
    else if (val == 2) 
    { 
        cout << "\nSSTF Disk Scheduling Algorithm :" << endl; 
        shortestSeekTimeFirst(arr, 50, 8); 
        cout << "\n" 
             << endl; 
 
        goto label; 
    } 
    else if (val == 3) 
    { 
        cout << "\nSCAN Disk Scheduling Algorithm :" << endl; 
        string direction = "left"; 
        SCAN(arr, head, direction); 
        cout << "\n" 
             << endl; 
        goto label; 
    } 
    else if (val == 4) 
    { 
        cout << "\nC-SCAN Disk Scheduling Algorithm :" << endl; 
        cout << "Initial position of head: " << head << endl; 
        CSCAN(arr, head); 
        cout << "\n" 
             << endl; 
        goto label; 
    } 
    else if (val == 5) 
    { 
        cout << "\nLOOK Disk Scheduling Algorithm :" << endl; 
        string direction1 = "right"; 
        cout << "Initial position of head: " << head << endl; 
        LOOK_DISC(arr, head, direction1); 
        cout << "\n" 
             << endl; 
        goto label; 
    } 
    else if (val == 6) 
    { 
        cout << "\nC-LOOK Disk Scheduling Algorithm :" << endl; 
        cout << "Initial position of head: " << head << endl; 
        CLOOK(arr, head); 
        goto label; 
    } 
    else if (val == 7) 
    { 
        cout << "\nFCFS Disk Scheduling Algorithm :" << endl; 
        FCFS(arr, head); 
        cout << "\t" 
             << endl; 
        cout << "\nSSTF Disk Scheduling Algorithm :" << endl; 
        shortestSeekTimeFirst(arr, 50, 8); 
        cout << "\t" 
             << endl; 
        cout << "\nSCAN Disk Scheduling Algorithm :" << endl; 
        string direction = "left"; 
        SCAN(arr, head, direction); 
        cout << "\t" 
             << endl; 
        cout << "\nC-SCAN Disk Scheduling Algorithm :" << endl; 
        cout << "Initial position of head: " << head << endl; 
        CSCAN(arr, head); 
        cout << "\t" 
             << endl; 
        cout << "\nLOOK Disk Scheduling Algorithm :" << endl; 
        string direction1 = "right"; 
        cout << "Initial position of head: " << head << "\t"; 
        LOOK_DISC(arr, head, direction1); 
        cout << "\t" 
             << endl; 
        cout << "\nC-LOOK Disk Scheduling Algorithm :" << endl; 
        cout << "Initial position of head: " << head << endl; 
        CLOOK(arr, head); 
 
        compare(); 
 
        goto label; 
    } 
    else if (val == 8) 
    { 
 
        return 0; 
    } 
    else 
    { 
        cout << "invalid choice"; 
 
        goto label; 
    } 
 
    return 0; 
} 