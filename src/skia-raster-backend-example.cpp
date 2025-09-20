#include "include/core/SkData.h"
#include "include/core/SkImage.h"
#include "include/core/SkPaint.h"
#include "include/core/SkStream.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"
#include "include/encode/SkPngEncoder.h"

#include "common.h"

void draw(SkCanvas* canvas) {
    SkPaint paint;
    paint.setColor(SK_ColorGRAY);
    canvas->drawPaint(paint);
    paint.setColor(SK_ColorBLACK);
    canvas->drawRect({100, 200, 300, 500}, paint);
}

int main() {
    int width = 800;
    int height = 600;
    const char* file_path = "test.png";

    sk_sp<SkSurface> raster_surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(width, height));
    SkCanvas* raster_canvas = raster_surface->getCanvas();
    draw(raster_canvas);

    sk_sp<SkImage> image(raster_surface->makeImageSnapshot());
    if (!image) {
        ERROR("failed to create image from raster surface\n");
        return EXIT_FAILURE;
    }

    sk_sp<SkData> png_data = SkPngEncoder::Encode(nullptr, image.get(), {});
    if (!png_data) {
        ERROR("failed to encode png\n");
        return EXIT_FAILURE;
    }

    SkFILEWStream out(file_path);
    void(out.write(png_data->data(), png_data->size()));
}
