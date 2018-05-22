<template>
  <div id="index">
    <!--<el-container>

      <el-main>main</el-main>

    </el-container>-->
    <el-container direction="vertical">
    <nb-head></nb-head>
    <el-main>

        <el-row :gutter="20">
          <el-col :span="12" :offset="6">
            <div style="padding: 14px;" class="introduction">
              <span class="headline">NB-Iot开源云平台</span>
            </div>
            <el-card :body-style="{ padding: '5px' }" shadow="hover">
              <img src="./../assets/images/NB-IoT-header.png" class="image">
              <div style="padding: 14px;" class="introduction">
                <span class="content">一套解决当下窄带物联网数据透传的方案, 简单快速</span>
              </div>
            </el-card>
          </el-col>
        </el-row>
      <el-row class="null"></el-row>

        <el-row :gutter="20">
          <el-col :span="6" :offset="2">
            <el-card :body-style="{ padding: '5px' }" shadow="hover">
              <img src="./../assets/images/NBIot2.jpg" class="image"></img>
              <div style="padding: 14px;" class="introduction">
                <h3>介绍</h3>
                <p>阅读介绍，了解NB-Iot的方方面面</p> <br><br><br>
                <el-button type="primary" round class="detail_button">查看详情</el-button>
              </div>
            </el-card>
          </el-col>
          <el-col :span="6" :offset="1">
            <el-card :body-style="{ padding: '5px' }" shadow="hover">
              <img src="./../assets/images/monitoring_NB-IoT.png" class="image"></img>
              <div style="padding: 14px;" class="introduction">
                <h3>API</h3>
                <p>提供终端SDK、APP SDK，开放丰富的REST API接口，集成消息推送接口</p><br><br>
                <el-button type="primary" round class="detail_button">查看详情</el-button>
              </div>
            </el-card>
          </el-col>
          <el-col :span="6" :offset="1">
            <el-card :body-style="{ padding: '20px' }" shadow="hover">
              <img src="./../assets/images/nb_iot.png" class="image"></img>
              <div style="padding: 14px;" class="introduction">
                <h3>设备管理</h3>
                <p>终端注册开通与生命周期管理，提供状态、故障、流量的不间断监控</p>
                <el-button type="primary" round class="detail_button">查看详情</el-button>
              </div>
            </el-card>
          </el-col>
        </el-row>
      <el-row class="null"></el-row>
    </el-main>
    <nb-foot></nb-foot>
    </el-container>
  </div>
</template>

<script>
  import nbHeader from "../components/nbHeader";
  import nbFooter from "../components/nbFooter";
  import './../assets/css/index.css';
    export default {
        name: "index",
        components: {
          'nb-head': nbHeader,
          'nb-foot': nbFooter
        }
    }
</script>

<style scoped>

</style>
