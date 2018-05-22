<template>
    <div>
      <!--<el-container direction="vertical" class="mainConCon">-->
        <el-main class="mainConCon">

          <el-row :gutter="20">

            <el-col :span="6">
              <el-card :body-style="{ padding: '0px' }" shadow="hover">
                <el-row :gutter="20">
                  <el-col :span="12">
                  <div style="padding: 5px;" class="cardImageset">
                    <img src="./../assets/images/mainControl/deviceNum.png" class="cardImageSet">
                  </div>
                  </el-col>
                  <el-col :span="10">
                    <br>
                    <el-row :gutter="20">
                      <li class="cardName" style="list-style-type: none; font-size: 30px; float: right; ">设备数量</li>
                    </el-row>
                    <!--<el-row class="null"></el-row>-->
                    <br><br>
                    <el-row :gutter="20">
                      <li class="cardName" style="list-style-type: none; font-size: 25px; float: right; color: #c22356">1</li>
                    </el-row>
                  </el-col>
                </el-row>
              </el-card>
            </el-col>

            <el-col :span="6">
              <el-card :body-style="{ padding: '0px' }" shadow="hover">
                <el-row :gutter="20">
                  <el-col :span="12">
                    <div style="padding: 5px;" class="cardImageset">
                      <img src="./../assets/images/mainControl/deviceListNum.png" class="cardImageSet">
                    </div>
                  </el-col>
                  <el-col :span="10">
                    <br>
                    <el-row :gutter="20">
                      <li class="cardName" style="list-style-type: none; font-size: 30px; float: right;">上行数据</li>
                    </el-row>
                    <!--<el-row class="null"></el-row>-->
                    <br><br>
                    <el-row :gutter="20">
                      <li class="cardName" style="list-style-type: none; font-size: 25px; float: right; color: #c22356">1</li>
                    </el-row>
                  </el-col>
                </el-row>
              </el-card>
            </el-col>

            <el-col :span="6">
              <el-card :body-style="{ padding: '0px' }" shadow="hover">
                <el-row :gutter="20">
                  <el-col :span="12">
                    <div style="padding: 5px;" class="cardImageset">
                      <img src="./../assets/images/mainControl/othersMsg.png" class="cardImageSet">
                    </div>
                  </el-col>
                  <el-col :span="10">
                    <br>
                    <el-row :gutter="20">
                      <li class="cardName" style="list-style-type: none; font-size: 30px; float: right;">下行数据</li>
                    </el-row>
                    <!--<el-row class="null"></el-row>-->
                    <br><br>
                    <el-row :gutter="20">
                      <li class="cardName" style="list-style-type: none; font-size: 25px; float: right; color: #c22356">1</li>
                    </el-row>
                  </el-col>
                </el-row>
              </el-card>
            </el-col>

            <el-col :span="6">
              <el-card :body-style="{ padding: '0px' }" shadow="hover">
                <el-row :gutter="20">
                  <el-col :span="12">
                    <div style="padding: 5px;" class="cardImageset">
                      <img src="./../assets/images/mainControl/usersNum.png" class="cardImageSet">
                    </div>
                  </el-col>
                  <el-col :span="10">
                    <br>
                    <el-row :gutter="20">
                      <li class="cardName" style="list-style-type: none; font-size: 30px; ">用户数量</li>
                    </el-row>
                    <!--<el-row class="null"></el-row>-->
                    <br><br>
                    <el-row :gutter="20">
                      <li class="cardName" style="list-style-type: none; font-size: 25px; float: right; color: #c22356">1</li>
                    </el-row>
                  </el-col>
                </el-row>
              </el-card>
            </el-col>
          </el-row>

          <el-row class="null"></el-row>

          <el-row :gutter="20">
            <el-col :span="24">
              <el-card class="box-card">
                <div slot="header" class="clearfix">
                  <span>设备在线情况</span>
                  <!--<el-button style="float: right; padding: 3px 0" type="text">操作按钮</el-button>-->
                </div>
                <div class="bottom" id="deStatistics" style="width: 1200px;height:400px;"></div>
              </el-card>
            </el-col>

            <el-col :span="24">
              <el-card class="box-card">
                <div slot="header" class="clearfix">
                  <span>近24小时流量统计</span>
                  <!--<el-button style="float: right; padding: 3px 0" type="text">操作按钮</el-button>-->
                </div>
                <div class="bottom" id="deFlowStatistics" style="width: 1200px;height:400px;"></div>
              </el-card>
            </el-col>
          </el-row>
          <el-row class="null"></el-row>
          <el-row :gutter="20">
            <el-col :span="24">
              <el-card class="box-card">
                <div slot="header" class="clearfix">
                  <span>UDP数据流量统计</span>
                  <!--<el-button style="float: right; padding: 3px 0" type="text">操作按钮</el-button>-->
                </div>
                <div class="bottom" id="deUDPFlowStatistics" style="width: 1200px;height:400px;"></div>
              </el-card>
            </el-col>

            <el-col :span="24">
              <el-card class="box-card">
                <div slot="header" class="clearfix">
                  <span>CoAP数据流量统计</span>
                  <!--<el-button style="float: right; padding: 3px 0" type="text">操作按钮</el-button>-->
                </div>
                <div class="bottom" id="deCoAPFlowStatistics" style="width: 1200px;height:400px;"></div>
              </el-card>
            </el-col>
          </el-row>
          <el-row>
            <!--<div class="bottom" id="main" style="width: 600px;height:400px;"></div>-->
          </el-row>
        </el-main>

      <!--</el-container>-->
    </div>
</template>

<script>
  var echarts = require('echarts/lib/echarts');
  require("echarts/lib/chart/line");
  require("echarts/lib/chart/lines");
  require('echarts/lib/component/tooltip');
  require('echarts/lib/component/title');
  require("echarts/lib/chart/pie");
  import "./../assets/css/mainControl.css"
    export default {
        name: "main-control",
        mounted() {
          let deviceStatistics = echarts.init(document.getElementById('deStatistics'));
          let colors = ['#5793f3', '#d14a61', '#675bba'];
          // 指定图表的配置项和数据
          let option1 = {
            color: colors,

            tooltip: {
              trigger: 'none',
              axisPointer: {
                type: 'cross'
              }
            },
            legend: {
              data:['设备1', '设备2']
            },
            grid: {
              top: 70,
              bottom: 50
            },
            xAxis: [
              {
                type: 'category',
                axisTick: {
                  alignWithLabel: true
                },
                axisLine: {
                  onZero: false,
                  lineStyle: {
                    color: colors[1]
                  }
                },
                axisPointer: {
                  label: {
                    formatter(params) {
                      return '在线  ' + params.value
                        + (params.seriesData.length ? '：' + params.seriesData[0].data : '');
                    }
                  }
                },
                data: ["2016-1", "2016-2", "2016-3", "2016-4", "2016-5", "2016-6", "2016-7", "2016-8", "2016-9", "2016-10", "2016-11", "2016-12"]
              },
              {
                type: 'category',
                axisTick: {
                  alignWithLabel: true
                },
                axisLine: {
                  onZero: false,
                  lineStyle: {
                    color: colors[0]
                  }
                },
                axisPointer: {
                  label: {
                    formatter(params) {
                      return '在线  ' + params.value
                        + (params.seriesData.length ? '：' + params.seriesData[0].data : '');
                    }
                  }
                },
                data: ["2015-1", "2015-2", "2015-3", "2015-4", "2015-5", "2015-6", "2015-7", "2015-8", "2015-9", "2015-10", "2015-11", "2015-12"]
              }
            ],
            yAxis: [
              {
                type: 'value'
              }
            ],
            series: [
              {
                name:'设备1',
                type:'line',
                xAxisIndex: 1,
                smooth: true,
                data: [2.6, 5.9, 9.0, 26.4, 28.7, 70.7, 175.6, 182.2, 48.7, 18.8, 6.0, 2.3]
              },
              {
                name:'设备2',
                type:'line',
                smooth: true,
                data: [3.9, 5.9, 11.1, 18.7, 48.3, 69.2, 231.6, 46.6, 55.4, 18.4, 10.3, 0.7]
              }
            ]
          };
          // 使用刚指定的配置项和数据显示图表。
          deviceStatistics.setOption(option1);


          let deviceFlowStatistics = echarts.init(document.getElementById('deFlowStatistics'));
          let option2 = {
            tooltip : {
              trigger: 'item',
              formatter: "{a} <br/>{b} : {c} ({d}%)"
            },
            legend: {
              orient: 'vertical',
              left: 'left',
              data: ['设备1','设备2']
            },
            series: [
              {
                name: '访问来源',
                type: 'pie',
                radius : '55%',
                center: ['50%', '60%'],
                data:[
                  {value:335, name:'设备1'},
                  {value:310, name:'设备2'}
                ],
                itemStyle: {
                  emphasis: {
                    shadowBlur: 10,
                    shadowOffsetX: 0,
                    shadowColor: 'rgba(0, 0, 0, 0.5)'
                  }
                }
              }
            ]
          };
          deviceFlowStatistics.setOption(option2);


          let deviceUDPFlowStatistics = echarts.init(document.getElementById('deUDPFlowStatistics'));
          let colors3= ['#5793f3', '#d14a61', '#675bba'];
          // 指定图表的配置项和数据
          let option3 = {
            color: colors3,

            tooltip: {
              trigger: 'none',
              axisPointer: {
                type: 'cross'
              }
            },
            legend: {
              data:['设备1', '设备2']
            },
            grid: {
              top: 70,
              bottom: 50
            },
            xAxis: [
              {
                type: 'category',
                axisTick: {
                  alignWithLabel: true
                },
                axisLine: {
                  onZero: false,
                  lineStyle: {
                    color: colors[1]
                  }
                },
                axisPointer: {
                  label: {
                    formatter(params) {
                      return 'UDP  ' + params.value
                        + (params.seriesData.length ? '：' + params.seriesData[0].data : '');
                    }
                  }
                },
                data: ["2016-1", "2016-2", "2016-3", "2016-4", "2016-5", "2016-6", "2016-7", "2016-8", "2016-9", "2016-10", "2016-11", "2016-12"]
              },
              {
                type: 'category',
                axisTick: {
                  alignWithLabel: true
                },
                axisLine: {
                  onZero: false,
                  lineStyle: {
                    color: colors[0]
                  }
                },
                axisPointer: {
                  label: {
                    formatter(params) {
                      return 'UDP  ' + params.value
                        + (params.seriesData.length ? '：' + params.seriesData[0].data : '');
                    }
                  }
                },
                data: ["2015-1", "2015-2", "2015-3", "2015-4", "2015-5", "2015-6", "2015-7", "2015-8", "2015-9", "2015-10", "2015-11", "2015-12"]
              }
            ],
            yAxis: [
              {
                type: 'value'
              }
            ],
            series: [
              {
                name:'设备1',
                type:'line',
                xAxisIndex: 1,
                smooth: true,
                data: [2.6, 5.9, 9.0, 26.4, 28.7, 70.7, 175.6, 182.2, 48.7, 18.8, 6.0, 2.3]
              },
              {
                name:'设备2',
                type:'line',
                smooth: true,
                data: [3.9, 5.9, 11.1, 18.7, 48.3, 69.2, 231.6, 46.6, 55.4, 18.4, 10.3, 0.7]
              }
            ]
          };

          // 使用刚指定的配置项和数据显示图表。
          deviceUDPFlowStatistics.setOption(option3);


          let deviceCoAPFlowStatistics = echarts.init(document.getElementById('deCoAPFlowStatistics'));
          let colors4 = ['#5793f3', '#d14a61', '#675bba'];
          // 指定图表的配置项和数据
          let option4 = {
            color: colors4,

            tooltip: {
              trigger: 'none',
              axisPointer: {
                type: 'cross'
              }
            },
            legend: {
              data:['设备1', '设备2']
            },
            grid: {
              top: 70,
              bottom: 50
            },
            xAxis: [
              {
                type: 'category',
                axisTick: {
                  alignWithLabel: true
                },
                axisLine: {
                  onZero: false,
                  lineStyle: {
                    color: colors[1]
                  }
                },
                axisPointer: {
                  label: {
                    formatter(params) {
                      return 'CoAP  ' + params.value
                        + (params.seriesData.length ? '：' + params.seriesData[0].data : '');
                    }
                  }
                },
                data: ["2016-1", "2016-2", "2016-3", "2016-4", "2016-5", "2016-6", "2016-7", "2016-8", "2016-9", "2016-10", "2016-11", "2016-12"]
              },
              {
                type: 'category',
                axisTick: {
                  alignWithLabel: true
                },
                axisLine: {
                  onZero: false,
                  lineStyle: {
                    color: colors[0]
                  }
                },
                axisPointer: {
                  label: {
                    formatter(params) {
                      return 'CoAP  ' + params.value
                        + (params.seriesData.length ? '：' + params.seriesData[0].data : '');
                    }
                  }
                },
                data: ["2015-1", "2015-2", "2015-3", "2015-4", "2015-5", "2015-6", "2015-7", "2015-8", "2015-9", "2015-10", "2015-11", "2015-12"]
              }
            ],
            yAxis: [
              {
                type: 'value'
              }
            ],
            series: [
              {
                name:'设备1',
                type:'line',
                xAxisIndex: 1,
                smooth: true,
                data: [2.6, 5.9, 9.0, 26.4, 28.7, 70.7, 175.6, 182.2, 48.7, 18.8, 6.0, 2.3]
              },
              {
                name:'设备2',
                type:'line',
                smooth: true,
                data: [3.9, 5.9, 11.1, 18.7, 48.3, 69.2, 231.6, 46.6, 55.4, 18.4, 10.3, 0.7]
              }
            ]
          };

          // 使用刚指定的配置项和数据显示图表。
          deviceCoAPFlowStatistics.setOption(option4);

        }
    }
</script>

<style scoped>

</style>
