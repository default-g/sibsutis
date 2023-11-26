package com.example.livewallpaper;

import android.graphics.Bitmap;
import android.graphics.Matrix;
import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;

public class Fish {
    private float posX = 0.0f;
    private float posY = 0.0f;
    private float speed;
    private float xSpeedDirection = 2.0f;
    private float ySpeedDirection = 2.0f;
    private Bitmap image;
    private boolean isDead = false;
    private Matrix matrix = new Matrix();
    private int fieldWidth = 0;
    private int fieldHeight = 0;
    private final int border = 200;
    private int offsetY = 0;
    private final Random random = new Random();

    public Fish(Bitmap image, int fieldWidth, int fieldHeight, int offsetY, float speed) {
        this.image = image;
        this.speed = speed;
        this.fieldWidth = fieldWidth;
        this.fieldHeight = fieldHeight;
        this.offsetY = offsetY;

        int heightViaOffset = this.fieldHeight + this.offsetY - border;
        int widthWithBorder = fieldWidth - border;

        int posX = random.nextInt(widthWithBorder - border) + border;
        int posY = random.nextInt(heightViaOffset - this.offsetY) + this.offsetY;

        matrix.postTranslate((float) posX, (float) posY);
        this.posX = posX + this.image.getWidth() / 2.0f;
        this.posY = posY + this.image.getHeight() / 2.0f;
    }

    public void move() {
        if (!isDead) {
            collision();
            int int_random = ThreadLocalRandom.current().nextInt(0,50);
            if (int_random==1){
                xSpeedDirection *=(-1);
            }
            if (int_random==2){
                ySpeedDirection *=(-1);
            }
            posX += xSpeedDirection;
            posY += ySpeedDirection;
            matrix.postTranslate(xSpeedDirection, ySpeedDirection);
        } else {
            moveToSurface();
        }
    }

    public void moveToSurface() {
        if ((int) posY < offsetY) {
            ySpeedDirection = speed;
        } else if ((int) posY > offsetY) {
            ySpeedDirection = -speed;
        }

        posY += ySpeedDirection;
        matrix.postTranslate(0F, ySpeedDirection);
    }

    public void kill() {
        isDead = true;
        matrix = new Matrix();
        matrix.preRotate(180f, image.getWidth() / 2f, image.getHeight() / 2f);
        matrix.postTranslate(posX, posY);
    }

    public void revive() {
        isDead = false;
    }


    public boolean collision() {
        if (posX < border || posX + border > fieldWidth) {
            xSpeedDirection *= -1.0f;
            return true;
        } else if (posY < offsetY + border || posY + border > fieldHeight + offsetY) {
            ySpeedDirection *= -1.0f;
            return true;
        }

        return false;
    }

    public void setFieldSize(int width, int height, int offsetY) {
        fieldWidth = width;
        fieldHeight = height;
        this.offsetY = offsetY;
    }

    public boolean isDead() {
        return isDead;
    }

    public Bitmap getBitmap() {
        return image;
    }

    public Matrix getMatrix() {
        return matrix;
    }

}