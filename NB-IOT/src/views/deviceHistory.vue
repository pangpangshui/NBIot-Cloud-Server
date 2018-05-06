<template>
  <div class="maincontaint">
    <el-container direction="vertical" class="container">

      <el-row class="navbar">
        <el-header>
          <el-breadcrumb separator-class="el-icon-arrow-right">
            <el-breadcrumb-item :to="{ path: '/' }" replace>首页</el-breadcrumb-item>
            <el-breadcrumb-item >设备管理</el-breadcrumb-item>
            <el-breadcrumb-item :to="{ path: '/deviceList'}" replace>历史消息</el-breadcrumb-item>
          </el-breadcrumb>
        </el-header>

        <el-main>
          <el-row class="delistrow">

            <el-table v-loading="loading" border width="600" :data="tableData" stripe style="width: 100%" :default-sort = "{prop: 'index_t', order: 'descending'}">
              <el-table-column type="index" :index="indexMethod" label="序号" width="70" prop="index_t"></el-table-column>
              <el-table-column prop="deviceID" label="设备ID" sortable width="300" height="20"></el-table-column>
              <el-table-column prop="deviceData" label="数据" sortable width="300"></el-table-column>
              <el-table-column prop="date" label="日期" sortable width="300"></el-table-column>
            </el-table>

          </el-row>
        </el-main>
      </el-row>

    </el-container>
  </div>
</template>

<script>
  import axios from 'axios'
    export default {
      name: "device-history",
      data() {
        return {
          tableData: [],
          loading: true
        }
      },
      methods: {
        indexMethod(index) {
          return index;
        }
      },
      mounted() {
        axios.get("/deviceHistory", {}).then((response) => {

          this.tableData = response.data;
          this.loading = false;
          this.$notify({
            title: '成功',
            message: '成功加载历史消息',
            type: 'success'
          });
          console.log(response.data);
        })
      }
    }
</script>

<style scoped>

</style>
