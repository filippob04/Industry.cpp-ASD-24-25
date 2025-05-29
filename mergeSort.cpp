#include "mergeSort.h"

namespace list{ 
    void merge(List& l, int start, int mid, int end){

        int n1 = mid - start + 1;
        int n2 = end - mid;

        Elem* vSx = new Elem[n1];
        Elem* vDx = new Elem[n2];

        // Con due cicli for gestisco i dati con separazione mid e li pongo nei due array
        for(int i = 0; i < n1; i++){
            vSx[i] = l.list[start + i];
        }
        for(int i = 0; i < n2; i++){
            vDx[i] = l.list[mid + 1 + i];
        }

        int sxIndex = 0, dxIndex = 0, curIndex = start;

        while(sxIndex < n1 && dxIndex < n2) {
            if(vSx[sxIndex] < vDx[dxIndex]) {
                l.list[curIndex++] = vSx[sxIndex++];
            } else {
                l.list[curIndex++] = vDx[dxIndex++];
            }
        }

        while(sxIndex < n1) {
            l.list[curIndex++] = vSx[sxIndex++];
        }
        while(dxIndex < n2) {
            l.list[curIndex++] = vDx[dxIndex++];
        }

        delete[] vSx;
        delete[] vDx;
    

    }

    void mergeSort(List& l, int start, int end) {
        if(start < end) {
            int mid = (start + end) / 2;
            mergeSort(l, start, mid);
            mergeSort(l, mid + 1, end);
            merge(l, start, mid, end);
        }
    }
}