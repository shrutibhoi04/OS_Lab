
#include <stdio.h>
#include <limits.h>

#define MAX_FRAMES 10
#define MAX_PAGES 30

int pages[MAX_PAGES], frames[MAX_FRAMES], n, fsize;

// Function to check if a page is in frames
int isPageInFrames(int page) {
    for (int i = 0; i < fsize; i++)
        if (frames[i] == page) return 1;
    return 0;
}

// Function to display frames
void displayFrames() {
    printf("Frames: ");
    for (int i = 0; i < fsize; i++) {
        if (frames[i] == -1) printf("- ");
        else printf("%d ", frames[i]);
    }
    printf("\n");
}

// FIFO Page Replacement
void FIFO() {
    int page_faults = 0, next_replace = 0;
    for (int i = 0; i < n; i++) {
        if (!isPageInFrames(pages[i])) { // Page fault occurs
            frames[next_replace] = pages[i];
            next_replace = (next_replace + 1) % fsize; // FIFO rotation
            page_faults++;
            printf("Page fault at page %d: ", pages[i]);
            displayFrames();
        }
    }
    printf("FIFO Page Faults: %d\n", page_faults);
}

// LRU Page Replacement
void LRU() {
    int page_faults = 0, last_used[MAX_FRAMES];
    for (int i = 0; i < fsize; i++) last_used[i] = -1; // initialize last used
    for (int i = 0; i < n; i++) {
        if (!isPageInFrames(pages[i])) {
            int lru_index = 0, lru_value = INT_MAX;
            for (int j = 0; j < fsize; j++)
                if (last_used[j] < lru_value) { lru_value = last_used[j]; lru_index = j; }
            frames[lru_index] = pages[i];
            page_faults++;
            printf("Page fault at page %d: ", pages[i]);
            displayFrames();
        }
        for (int j = 0; j < fsize; j++)
            if (frames[j] == pages[i]) last_used[j] = i;
    }
    printf("LRU Page Faults: %d\n", page_faults);
}

// Optimal Page Replacement
void Optimal() {
    int page_faults = 0;
    for (int i = 0; i < n; i++) {
        if (!isPageInFrames(pages[i])) {
            int replace_index = 0, furthest = i;
            for (int j = 0; j < fsize; j++) {
                int next_use = INT_MAX;
                for (int k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) { next_use = k; break; }
                }
                if (next_use > furthest) { furthest = next_use; replace_index = j; }
            }
            frames[replace_index] = pages[i];
            page_faults++;
            printf("Page fault at page %d: ", pages[i]);
            displayFrames();
        }
    }
    printf("Optimal Page Faults: %d\n", page_faults);
}

int main() {
    int choice;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &fsize);

    printf("Choose Page Replacement Algorithm:\n1. FIFO\n2. LRU\n3. Optimal\n");
    scanf("%d", &choice);

    for (int i = 0; i < fsize; i++) frames[i] = -1; // Initialize frames

    switch (choice) {
        case 1: FIFO(); break;
        case 2: LRU(); break;
        case 3: Optimal(); break;
        default: printf("Invalid choice!\n"); break;
    }

    return 0;
}
