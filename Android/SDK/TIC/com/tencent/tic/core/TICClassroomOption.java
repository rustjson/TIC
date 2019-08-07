package com.tencent.tic.core;

import com.tencent.teduboard.TEduBoardController;

/**
 * 课堂参数配置
 */
public class TICClassroomOption{
    /**
     * 房间ID，由业务维护
     */
    public int classId = -1;

    /**
     * ntp服务器
     * @brief 进房成功后从ntp服务器获取服务器时间戳作为白板课后录制的对时信息，默认使用time1.cloud.tencent.com。为保证对时信息的高度一致，建议各端使用一样的对时地址。
     **/
    public String ntpServer = "time1.cloud.tencent.com";

    /**
     * 初始化白板的参数
     */
    public TEduBoardController.TEduBoardInitParam boardInitPara = null;

    /**
     * 白板事件回调接口监听，内部通过弱引用持有，请自已保持对象有效，否则会导致无回调
     */
    public TEduBoardController.TEduBoardCallback boardCallback = null;


    public int getClassId() {
        return classId;
    }

    public TICClassroomOption setClassId(int classId) {
        this.classId = classId;
        return this;
    }

    @Override
    public String toString() {
        return "TICClassroomOption{" +
                "classId=" + classId +
                ",ntpServer=" + ntpServer +
                ",boardInitPara=" + boardInitPara +
                ",boardCallback=" + boardCallback +
                '}';
    }
}
