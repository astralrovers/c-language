### 使用说明  

#### 一、snmp程序中使用说明
  1. snmp程序中用于snmp设备的注册，包含普通类型和table类型
  2. alarm_id_table包含在submodule中，用于多个工程共享，增加一个alarm项时，arm和snmp修改一处即可
  3. 添加新的机型时需要提供以下外部数据:
     - 对应机型的参数snmp-oid
     - 对应机型的参数arm-id与snmp-oid的映射
     - 对应机型的告警项
  4. 将三个表添加到device_list.c中的device_list，并完善对应机型的类型

#### 二、arm程序中使用说明
  1. arm程序中用于告警时查找告警项的名称
  2. 需要完善find_alarm_name.c中的device_list
