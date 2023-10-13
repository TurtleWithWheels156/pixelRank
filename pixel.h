#define SIZE 51

struct pixelData {
  int value;
  uint32_t x;
  uint32_t y;
};

void processRow(struct pixelData * topVals, uint16_t * array, uint32_t width, uint32_t row, int * pixelcount);
void pushRank(struct pixelData * topVals, int val, uint32_t width, uint32_t row);
void showRank();
