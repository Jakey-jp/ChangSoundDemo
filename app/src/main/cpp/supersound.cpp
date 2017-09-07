#include "inc/fmod.hpp"
#include <stdlib.h>
#include <unistd.h>
#include "com_hjp_mysound_Utils.h"

#include <android/log.h>
//日志输出宏定义
#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO,"jakey",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"jakey",FORMAT,##__VA_ARGS__);

//变声的类型
#define MODE_NORMAL 0//正常
#define MODE_LUOLI 1//萝莉
#define MODE_DASHU 2//大叔
#define MODE_JINGSONG 3//惊悚
#define MODE_GAOGUAI 4//搞怪
#define MODE_KONGLING 5//空灵

//使用fmod的命名空间
using namespace FMOD;

Channel *channel;
bool paused = false;

//Java native方法的实现
JNIEXPORT void JNICALL Java_com_hjp_mysound_Utils_fix(JNIEnv *env,
                                                      jclass type_, jstring path_, jint type) {

    //初始化
    const char *path = env->GetStringUTFChars(path_, NULL);
    System *system;
    Sound *sound;
    DSP *dsp;
    bool playing = true;

    float frequency = 0;

    //fmod初始化
    System_Create(&system);
    //指定最大的声轨数等参数
    system->init(32, FMOD_INIT_NORMAL, NULL);


    try {

        //创建声音
        system->createSound(path, FMOD_DEFAULT, NULL, &sound);

        switch (type) {
            case MODE_NORMAL:
                //原声播放
                LOGI("%s", path);
                //指定的是音轨0，最后update的时候才会播放
                system->playSound(sound, 0, false, &channel);
                LOGI("%s", "fix normal");
                break;
            case MODE_LUOLI:
                //loli
                //DSP digital singal process
                //dsp->音效
                //dsp 提升或者降低音调的一种音效
                //创建一个数字信号处理对象DSP
                //DSP（数字信号处理）主要原理是：通过改变声音的两个参数：响度（振幅） 声调（频率）
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                //设置参数，提高频率，升高一个八度
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 8.0);
                //把处理对象添加到Channel的音轨0中(注意这里要先播放然后添加音轨特效)
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                LOGE("%s", "luo li");
                break;
            case MODE_DASHU:
                //大叔
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                //设置音调的参数
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.8);
                //添加进到channel
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                LOGE("%s", "da shu");
                break;
            case MODE_JINGSONG:
                //惊悚
                system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 5);
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
            case MODE_GAOGUAI:
                //搞怪
                //提高说话的速度
                system->playSound(sound, 0, false, &channel);
                channel->getFrequency(&frequency);
                frequency = frequency * 2;
                channel->setFrequency(frequency);
                LOGI("%s", "fix gaoguai");
                break;
            case MODE_KONGLING:
                //空灵
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);
                dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 20);
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                LOGI("%s", "fix kongling");
                break;
            default:

                break;
        }
    } catch (...) {
        //CMake默认支持异常处理。
        //播放的时候可能会有异常，例如文件找不到等等，然后把异常抛给Java
        LOGE("%s", "发生异常");
        goto end;
    }

    //update的时候才会播放
    system->update();

    //每秒钟判断一下是否在播放
    while (playing) {
        channel->isPlaying(&playing);
        usleep(1 * 1000 * 1000);//单位是微妙，这里是1秒延时
//        channel->setPaused(!paused);
//        channel->getPaused(&paused);
    }

    goto end;

    end:
    //释放资源
    env->ReleaseStringUTFChars(path_, path);
    sound->release();
    system->close();
    system->release();
}

JNIEXPORT void JNICALL Java_com_hjp_mysound_Utils_pause(JNIEnv *env, jclass type_)  {
    LOGE("%s", "pause");
//    isPlaying= false;
    channel->setPaused(!paused);
    channel->getPaused(&paused);
//    channel->stop();
}
