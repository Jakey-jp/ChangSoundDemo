package com.hjp.mysound;
/**
 * Created by jakey on 2017/3/5.
 * QQ 784990536
 */
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;

import org.fmod.FMOD;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });
        FMOD.init(this);
    }


    public void mFix(final View v) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                //音频路径可以去获取麦克风的数据，我这里写死了
                String path = "file:///android_asset/jakey.m4a";
                switch (v.getId()) {
                    case R.id.btn_normal:
                        Utils.fix(path, Utils.MODE_NORMAL);
                        break;
                    case R.id.btn_luoli:
                        Utils.fix(path, Utils.MODE_LUOLI);
                        break;
                    case R.id.btn_dashu:
                        Utils.fix(path, Utils.MODE_DASHU);
                        break;
                    case R.id.btn_jingsong:
                        Utils.fix(path, Utils.MODE_JINGSONG);
                        break;
                    case R.id.btn_gaoguai:
                        Utils.fix(path, Utils.MODE_GAOGUAI);
                        break;
                    case R.id.btn_kongling:
                        Utils.fix(path, Utils.MODE_KONGLING);
                        break;
                    default:
                        break;
                }
            }
        }).start();

    }

    public void pause(View v) {
        Utils.pause();

    }
    @Override
    protected void onDestroy() {
        // TODO Auto-generated method stub
        super.onDestroy();
        FMOD.close();
    }
}
