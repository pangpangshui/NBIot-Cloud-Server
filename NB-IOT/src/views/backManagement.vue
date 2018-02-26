<template>
  <div>
    <nb-head></nb-head>
    <el-main>
      <h1>后台管理系统</h1>
      <el-button @click="linkCoapServer">访问coap服务器</el-button>
    </el-main>
  </div>
</template>

<script>
    import nbHeader from "../components/nbHeader";
    import axios from 'axios'
    export default {
        name: "back-management",
        components: {
          'nb-head': nbHeader,
        },
        methods: {
          linkCoapServer() {
            axios.post("/coap", {}).then( (response) => {

            })
          }
        }

    }
</script>

<style scoped>

</style>
