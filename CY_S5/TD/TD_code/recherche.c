//
// Created by 金卓远 on 24-11-6.
//


int recherche1(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return 1; // 找到元素，返回 1
        }
    }
    return 0; // 未找到元素，返回 0
}

int recherche2(int arr[], int size, int target) {
    int flag=0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            flag = 1; // 找到元素，返回 1
        }
    }
    return flag; // 未找到元素，返回 0
}

