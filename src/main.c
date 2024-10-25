#include "includes/app.h"

int main(void) {

  struct App *app = create_app();
  if (app) {
    run_app(app);
    destroy_app(&app);
  }

  return 0;
}
