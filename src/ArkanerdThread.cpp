#include "ArkanerdThread.h"
#include "ArkanerdCanvas.h"

namespace arkanerd {

	ArkanerdThread::ArkanerdThread(ArkanerdCanvas *canvas)
    : canvas_(canvas) {
	}

	void ArkanerdThread::start() {
	}

	void ArkanerdThread::pause() {
	}

	void ArkanerdThread::resumeGame() {
	}

	void ArkanerdThread::stop() {
	}

	void ArkanerdThread::run() {
    // Flush any keystrokes that occurred before the
    // game started:
		canvas_->flushKeys();
		canvas_->setThread(this);
		canvas_->nextLevel();
		while (true) {
			canvas_->render();
			canvas_->input();
			canvas_->update();
			canvas_->checkCollisions();
		}
  }

} // namespace arkanerd
