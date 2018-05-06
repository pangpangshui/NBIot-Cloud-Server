<template>
  <div class="maincontaint">
    <el-container direction="vertical" class="container">

      <el-row class="navbar">
        <el-header>
          <el-breadcrumb separator-class="el-icon-arrow-right">
            <el-breadcrumb-item :to="{ path: '/' }" replace>首页</el-breadcrumb-item>
            <el-breadcrumb-item >设备管理</el-breadcrumb-item>
            <el-breadcrumb-item :to="{ path: '/debugDevice'}" replace>数据传输</el-breadcrumb-item>
          </el-breadcrumb>
        </el-header>

        <el-main>
          <el-row class="delistrow">

            <el-form label-width="100px" class="createdevices" :inline="true" v-bind:model="deviceInfo">
              <el-row>
                <div class="panel-header">数据传输</div>
              </el-row>
              <el-row class="devicebody">
                <el-col :span="24">
                <!--<el-form-item>-->
                  <el-input readonly type="textarea" :rows="18"></el-input>
                <!--</el-form-item>-->
                </el-col>
              </el-row>

              <el-row class="devicebody" :gutter="30">
                <el-col :span="20">
                  <el-input>请输入需要发送的数据</el-input>
                </el-col>
                <el-col :span="4">
                  <el-button>发送</el-button>
                </el-col>
              </el-row>

              <el-row class="devicebody" :gutter="30">
                <el-col :span="6">
                  <!--<el-checkbox-group>-->
                  <el-checkbox label="按16进制发送"></el-checkbox>
                  <el-checkbox label="加回车换行符"></el-checkbox>
                  <!--</el-checkbox-group>-->
                </el-col>
                <el-col :span="6">

                </el-col>
              </el-row>

            </el-form>

          </el-row>
        </el-main>
      </el-row>

    </el-container>
  </div>
</template>

<script>
  import Bus from './../API/bus'
  import axios from 'axios'
    export default {
      name: "debug-device",
      data() {
        return {
          deviceInfo: {
            deviceID: '',
            devicePwd: '',
            deviceName: '',
            deviceAddr: '',
            deviceDetail: ''
          },
        }
      },
      mounted() {
        Bus.$on('getDeviceInfo', row => {
            console.log(row);
            this.deviceInfo = row;
        });
        // axios.post("/debugDevice/{deviceID}").then((response) => {
        //   this.tableData = response.data;
        //   this.loading = false;
        //   this.$notify({
        //     title: '成功',
        //     message: '成功加载您的设备信息',
        //     type: 'success'
        //   });
        //   console.log(response.data);
        // })
      }
    }
</script>

<style scoped>

</style>
