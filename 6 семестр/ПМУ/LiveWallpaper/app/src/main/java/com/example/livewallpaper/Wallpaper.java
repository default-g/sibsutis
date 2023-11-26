package com.example.livewallpaper;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.os.BatteryManager;
import android.os.Handler;
import android.service.wallpaper.WallpaperService;
import android.view.SurfaceHolder;
import java.util.ArrayList;
import java.util.List;

public class Wallpaper extends WallpaperService  {

    private float batteryLevel = 1F;
    private List<Fish> fishList = new ArrayList<>();

    @Override
    public void onCreate() {
        super.onCreate();

        BroadcastReceiver receiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                if(intent != null) {
                    batteryLevel = intent.getIntExtra(BatteryManager.EXTRA_LEVEL, 100) / 100F;
                }
            }
        };

        registerReceiver(receiver, new IntentFilter(Intent.ACTION_BATTERY_CHANGED));
    }

    @Override
    public Engine onCreateEngine() {
        return new WallpaperEngine();
    }

    private class WallpaperEngine extends Engine {
        private final Handler m_handler = new Handler();
        private boolean m_visible = true;
        private boolean m_fieldSet = false;
        private Bitmap water = BitmapFactory.decodeResource(getResources(), R.drawable.water);

        private final Runnable drawRunner = () -> draw();

        @Override
        public void onCreate(SurfaceHolder surfaceHolder) {
            super.onCreate(surfaceHolder);
        }

        @Override
        public void onVisibilityChanged(boolean visible) {
            m_visible = visible;
            if (visible) {
                m_handler.post(drawRunner);
            } else {
                m_handler.removeCallbacks(drawRunner);
            }
        }

        @Override
        public void onSurfaceDestroyed(SurfaceHolder holder) {
            super.onSurfaceDestroyed(holder);
            m_visible = false;
            m_handler.removeCallbacks(drawRunner);
        }

        @Override
        public void onOffsetsChanged(
                float xOffset,
                float yOffset,
                float xStep,
                float yStep,
                int xPixels,
                int yPixels) {
            m_handler.post(drawRunner);
        }

        void draw() {
            SurfaceHolder holder = getSurfaceHolder();
            Canvas canvas = null;

            try {
                canvas = holder.lockCanvas();

                if (canvas != null) {
                    float offsetY = canvas.getHeight() * (1F - batteryLevel) ;
                    Bitmap scaledWater = Bitmap.createScaledBitmap(water, canvas.getWidth(), canvas.getHeight() - (int) offsetY, false);
                    Matrix matrix = new Matrix();

                    matrix.postTranslate(0F, offsetY);

                    if (fishList.size() < 5) {
                        Bitmap bitmap1 = BitmapFactory.decodeResource(getResources(), R.drawable.fish);
                        Bitmap bitmap2 = BitmapFactory.decodeResource(getResources(), R.drawable.fish2);
                        Bitmap bitmap3 = BitmapFactory.decodeResource(getResources(), R.drawable.fish3);
                        Bitmap bitmap4 = BitmapFactory.decodeResource(getResources(), R.drawable.fish4);
                        Bitmap bitmap5 = BitmapFactory.decodeResource(getResources(), R.drawable.fish5);

                        fishList.add(new Fish(bitmap1, scaledWater.getWidth(), scaledWater.getHeight(), (int) offsetY, 3F));
                        fishList.add(new Fish(bitmap2, scaledWater.getWidth(), scaledWater.getHeight(), (int) offsetY, 4F));
                        fishList.add(new Fish(bitmap3, scaledWater.getWidth(), scaledWater.getHeight(), (int) offsetY, 5F));
                        fishList.add(new Fish(bitmap4, scaledWater.getWidth(), scaledWater.getHeight(), (int) offsetY, 6F));
                        fishList.add(new Fish(bitmap5, scaledWater.getWidth(), scaledWater.getHeight(), (int) offsetY, 2F));

                    }

                    int deadFishCountNeed = (int) ((1F - batteryLevel) / (1F / fishList.size()));
                    int deadFishCountCur = 0;

                    for (Fish fish : fishList) {
                        if (fish.isDead()) deadFishCountCur++;
                    }

                    int i = 0;
                    while (deadFishCountCur != deadFishCountNeed && i < fishList.size()) {
                        if (deadFishCountCur > deadFishCountNeed) {
                            if (fishList.get(i).isDead()) fishList.get(i).revive();
                            deadFishCountCur--;
                        } else {
                            if (!fishList.get(i).isDead()) fishList.get(i).kill();
                            deadFishCountCur++;
                        }
                        i++;
                    }
                    canvas.drawColor(Color.WHITE);
                    canvas.drawBitmap(scaledWater, matrix, null);

                    for (Fish fish : fishList) {
                        fish.setFieldSize(scaledWater.getWidth(), scaledWater.getHeight(), (int) offsetY);
                        fish.move();
                        canvas.drawBitmap(fish.getBitmap(), fish.getMatrix(), null);
                    }
                }
            } finally {
                if (canvas != null) {
                    holder.unlockCanvasAndPost(canvas);
                }
            }

            m_handler.removeCallbacks(drawRunner);

            if (m_visible) {
                m_handler.postDelayed(drawRunner, 70);
            }

        }
    }

}