<template>
  <div>
    <el-row class="delistrow">
        <el-breadcrumb separator-class="el-icon-arrow-right">
          <el-breadcrumb-item :to="{ path: '/' }" replace>首页</el-breadcrumb-item>
          <el-breadcrumb-item >设备管理</el-breadcrumb-item>
          <el-breadcrumb-item :to="{ path: '/deviceList'}" replace>设备列表</el-breadcrumb-item>
        </el-breadcrumb>
    </el-row>

      <el-row class="delistrow">
        <el-button @click="createDevice('/createDevice')">创建设备</el-button>
      </el-row>

  </div>
</template>

<script>
    export default {
        name: "device-list",
      methods: {
        createDevice(url) {
          this.$router.push(url)
        }
      }
    }
</script>

<style scoped>
  .delistrow {
    margin-bottom: 20px;
    margin-left: 20px;
    &:last-child {
       margin-bottom: 0;
     }
  }
</style>
