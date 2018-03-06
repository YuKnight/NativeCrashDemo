//
// Created by 杨勇 on 2018/3/2.
//

#include <jni.h>
#include <android/log.h>
#include <signal.h>
#include <unistd.h>
#include <sstream>
#include <string.h>
#include "coffeecatch/coffeejni.h"
#include "coffeecatch/coffeecatch.h"

#define TAG "native-crash-activity.cpp"
#define LOG(str) __android_log_print(ANDROID_LOG_DEBUG,TAG,str)

//注册拦截器的信号
const int handledSignals[] = {
        SIGSEGV//11 C 无效的内存引用
        , SIGABRT//6 C 由abort(3)发出的退出指令
        , SIGFPE//8 C 浮点异常
        , SIGILL//4 C 非法指令
        , SIGBUS//10,7,10 C 总线错误(错误的内存访问)
        , SIGKILL //9 AEF Kill信号
        , SIGSTOP //17,19,23 DEF 终止进程
        , SIGTERM //15 A 终止信号
        , SIGTRAP //5 C 跟踪/断点捕获
};
//注册拦截器的信号 个数
const int handledSignalsNum = sizeof(handledSignals) / sizeof(handledSignals[0]);
//原信号handler
struct sigaction mold_handlers[handledSignalsNum];
struct sigaction mold_handler;

static JNIEnv *sigEnv;
static jobject sigObj;
static int mpid;

//信号 handler
void crash_sigaction(int signal, siginfo *info, void *reserved) {
    LOG("native- my_sigaction recived");
    int iPid = getpid();
    jclass cls = sigEnv->FindClass("chalilayang/com/nativecrashdemo/NativeCrashHandler");
    jmethodID tempmethodID = sigEnv->GetMethodID(cls, "onNativeCrash", "()V");
    switch (signal) {
        case SIGTRAP:
            LOG("native- SIGTRAP recived");
            sigEnv->CallVoidMethod(sigObj, tempmethodID);
            break;
        case SIGABRT:
            LOG("native- SIGABRT recived");
            sigEnv->CallVoidMethod(sigObj, tempmethodID);
            break;
        case SIGSEGV:
            LOG("native- SIGSEGV recived");
            sigEnv->CallVoidMethod(sigObj, tempmethodID);
            break;
        case SIGILL:
            LOG("native- SIGILL recived");
            sigEnv->CallVoidMethod(sigObj, tempmethodID);
            break;
        case SIGFPE:
            LOG("native- SIGFPE recived");
            sigEnv->CallVoidMethod(sigObj, tempmethodID);
            break;
        case SIGBUS:
            LOG("native- SIGBUS recived");
            sigEnv->CallVoidMethod(sigObj, tempmethodID);
            break;
        case SIGKILL:
            LOG("native- SIGKILL recived");
            sigEnv->CallVoidMethod(sigObj, tempmethodID);
            break;
        case SIGSTOP:
            LOG("native- SIGSTOP recived");
            sigEnv->CallVoidMethod(sigObj, tempmethodID);
            break;
        case SIGTERM:
            LOG("native- SIGTERM recived");
            sigEnv->CallVoidMethod(sigObj, tempmethodID);
            break;
        default:
            LOG("native- other signal");
            sigEnv->CallVoidMethod(sigObj, tempmethodID);
            break;
    }
}

//初始化 设置信号拦截器
void minitSigaction() {
    struct sigaction handler;
    memset(&handler, 0, sizeof(handler));
    handler.sa_sigaction = crash_sigaction;
    handler.sa_flags = SA_NOMASK;
    for (int i = 0; i < handledSignalsNum; ++i) {
        sigaction(handledSignals[i], &handler, &mold_handlers[i]);
    }
}

jint call_dangerous_function(JNIEnv* env, jobject object) {
    // ... do dangerous things!
    int * dd = NULL;
    *dd = 0;
    return 42;
}


#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jboolean
JNICALL
Java_chalilayang_com_nativecrashdemo_NativeCrashHandler_createNativeException(JNIEnv *env,
                                                                              jobject thiz) {
//    LOG("COFFEE");
//    int * dd = NULL;
//    LOG("COFFEE end");
}

JNIEXPORT void
JNICALL
Java_chalilayang_com_nativecrashdemo_NativeCrashHandler_initNativeHandler(JNIEnv *zenv,
                                                                          jobject thiz, int pid) {
//    sigEnv = zenv;
//    sigObj = (sigEnv)->NewGlobalRef(thiz);
//    mpid = pid;
//    minitSigaction();
}

#ifdef __cplusplus
}
#endif