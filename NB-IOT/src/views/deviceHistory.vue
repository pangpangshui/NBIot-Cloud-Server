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

            <el-row :gutter="20">
              <el-table v-loading="loading" border  height="600" width="600" :data="tableData.slice((currentPage-1)*pagesize,currentPage*pagesize)"
                        stripe style="width: 100%" :default-sort = "{prop: 'index_t', order: 'descending'}">
                <el-table-column type="index" :index="indexMethod" label="序号" width="70" prop="index_t"></el-table-column>
                <el-table-column prop="deviceID" label="设备ID" sortable width="280" height="20"></el-table-column>
                <el-table-column prop="deviceData" label="数据" sortable width="345"></el-table-column>
                <el-table-column prop="dataDir" label="上行/下行" sortable width="120"
                                 :filters="[{ text: '上行数据', value: '上行数据' }, { text: '下行数据', value: '下行数据' }]"
                                 :filter-method="dataDirFilter" filter-placement="bottom-end">
                </el-table-column>
                <el-table-column prop="protocol" label="协议" sortable width="100"
                                 :filters="[{ text: 'UDP', value: 'UDP' }, { text: 'CoAP', value: 'CoAP' }]"
                                 :filter-method="protocalFilter" filter-placement="bottom-end"></el-table-column>
                <el-table-column prop="date" label="日期" sortable width="300"></el-table-column>
              </el-table>
            </el-row>
            <el-row></el-row>
            <el-row :gutter="20">
              <el-col :span="6" :offset="12">
                <el-pagination class="paging" @size-change="handleSizeChange" @current-change="handleCurrentChange" :current-page="currentPage" background
                  :page-sizes="[10, 20, 50, 100]" :page-size="pagesize" layout="total, sizes, prev, pager, next, jumper" :total="tableData.length">
                </el-pagination>
              </el-col>
            </el-row>

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
          loading: true,
          currentPage:1,
          pagesize:20,
        }
      },
      methods: {
        indexMethod(index) {
          return index + 1;
        },
        dataDirFilter(value, row, column) {
          const property = column['property'];
          return row[property] === value;
        },
        protocalFilter(value, row, column) {
          const property = column['property'];
          return row[property] === value;
        },
        handleSizeChange(size) {
          this.pagesize = size;
        },
        handleCurrentChange(currentPage){
          this.currentPage = currentPage;
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
