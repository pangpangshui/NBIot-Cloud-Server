<template>
  <div>
    <el-main class="mainConCon">

      <el-row class="delistrow">
        <el-breadcrumb separator-class="el-icon-arrow-right">
          <el-breadcrumb-item :to="{ path: '/' }" replace>首页</el-breadcrumb-item>
          <el-breadcrumb-item >设备管理</el-breadcrumb-item>
          <el-breadcrumb-item :to="{ path: '/deviceList'}" replace>共享项目</el-breadcrumb-item>
        </el-breadcrumb>
      </el-row>

      <el-row class="delistrow">
        <h1>暂不支持</h1>
      </el-row>

    </el-main>
  </div>
</template>

<script>
    export default {
        name: "shared-project"
    }
</script>

<style scoped>

</style>
