<template>
  <div id="index">
    <!--<el-container>

      <el-main>main</el-main>

    </el-container>-->
    <el-container direction="vertical">
    <nb-head></nb-head>
    <el-main>
      <div>
        <div class="introduction">
          <h1>NB-Iot开源云平台</h1>
          <p>一套解决当下窄带物联网数据透传的方案, 简单快速</p>
        </div>
        <div class="indexImage">
          <img src="./../assets/images/image4.jpg"></img>
        </div>
        <div class="cards">
          <ul>
            <li class="card-item">
              <div class="card">
                <img src="./../assets/images/image2.png"></img>
                <h3>介绍</h3>
                <p>阅读介绍，了解NB-Iot的方方面面</p>
                <a href="/">查看详情</a>
              </div>
            </li>
            <li class="card-item">
              <div class="card">
                <img src="./../assets/images/image3.png"></img>
                <h3>API</h3>
                <p>API文档, 助力开发</p>
                <a href="/">查看详情</a>
              </div>
            </li>
            <li class="card-item">
              <div class="card">
                <img src="./../assets/images/image6.png"></img>
                <h3>预留</h3>
                <p>预留位</p>
                <a href="/">查看详情</a>
              </div>
            </li>
          </ul>
        </div>
      </div>
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
