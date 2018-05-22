<template>
  <div>
    <el-main class="mainConCon">

      <el-row class="delistrow">
        <el-breadcrumb separator-class="el-icon-arrow-right">
          <el-breadcrumb-item :to="{ path: '/' }" replace>首页</el-breadcrumb-item>
          <el-breadcrumb-item >设备管理</el-breadcrumb-item>
          <el-breadcrumb-item :to="{ path: '/deviceList'}" replace>用户信息</el-breadcrumb-item>
        </el-breadcrumb>
      </el-row>

      <el-row class="delistrow">
        <el-table border width="1200" :data="userData" stripe style="width: 150%">

          <el-table-column prop="userName" label="用户名" sortable width="200" height="20"></el-table-column>
          <el-table-column prop="Email" label="邮箱" sortable width="150"></el-table-column>
          <el-table-column prop="phone" label="电话" sortable width="175"></el-table-column>
          <el-table-column prop="QQ" label="QQ" sortable width="175"></el-table-column>
          <el-table-column prop="address" label="地址" sortable width="175"></el-table-column>
          <el-table-column prop="operation" label="操作" width="100">
            <template slot-scope="scope">
              <el-button @click="userInfoFormVisible = true" type="text" size="small">修改</el-button>
            </template>
          </el-table-column>
        </el-table>

        <el-dialog title="修改用户信息" :visible.sync="userInfoFormVisible" :before-close="handleClose" width="30%">
          <el-form :model="userForm">
            <el-form-item label="用户名" :label-width="formLabelWidth">
              <el-input v-model="userForm.name" auto-complete="off"></el-input>
            </el-form-item>
            <el-form-item label="邮箱" :label-width="formLabelWidth">
              <el-input v-model="userForm.email" auto-complete="off"></el-input>
            </el-form-item>
            <el-form-item label="电话" :label-width="formLabelWidth">
              <el-input v-model="userForm.phone" auto-complete="off"></el-input>
            </el-form-item>
            <el-form-item label="QQ" :label-width="formLabelWidth">
              <el-input v-model="userForm.qq" auto-complete="off"></el-input>
            </el-form-item>
            <el-form-item label="地址" :label-width="formLabelWidth">
              <el-input v-model="userForm.add" auto-complete="off"></el-input>
            </el-form-item>
          </el-form>
          <div slot="footer" class="dialog-footer">
            <el-button @click="userInfoFormVisible = false">取 消</el-button>
            <el-button type="primary" @click="moUserInfo">确 定</el-button>
          </div>
        </el-dialog>
      </el-row>

    </el-main>
  </div>
</template>

<script>
  import axios from 'axios'
    export default {
        name: "modify-user-info",
        data() {
          return {
            userData: [
              { userName:sessionStorage.userName, Email:'', phone:'', QQ:'', address:''}
            ],
            userInfoFormVisible: false,
            userForm: {
              name: '',
              email: '',
              phone: '',
              qq: '',
              add: ''
            },
            formLabelWidth: '120px'
          }
        },
      methods: {
        moUserInfo() {
          axios.post("/modifyUserInfo", {
            userName: this.userForm.name,
            userEmail: this.userForm.email,
            userPhone: this.userForm.phone,
            userQQ: this.userForm.qq,
            userAdd: this.userForm.add
          }).then((response) => {
            let res = response.data;
            console.log(res);
            if (res.status == "1") {
              // this.loginInfo.nickName = res.result.userName;
              this.$notify({
                title: '成功',
                message: '修改成功',
                type: 'success'
              });
              for (let userda in this.userData) {
                this.userData[userda]['userName'] = res.result.userName;
                this.userData[userda]['Email'] = res.result.userEmail;
                this.userData[userda]['phone'] = res.result.userPhone;
                this.userData[userda]['QQ'] = res.result.userQQ;
                this.userData[userda]['address'] = res.result.userAdd;
                localStorage.setItem('userda',JSON.stringify(res.result));
              }
              location.reload();//刷新页面
              // this.userData = res.result;
              this.userInfoFormVisible = false;

            } else {
              this.$notify.error({
                title: '错误',
                message: '修改失败'
              });
            }
          })
        },

        handleClose(done) {
          this.$confirm('确认关闭？')
            .then(_ => {
              done();
            })
            .catch(_ => {});
        }

      },
        mounted() {
          for (let userda in this.userData) {
            this.userForm = JSON.parse(localStorage.userda);
            console.log(this.userForm);
            this.userData[userda] = JSON.parse(localStorage.userda);
            this.userData[userda]['userName'] = this.userForm.userName;
            this.userData[userda]['Email'] = this.userForm.userEmail;
            this.userData[userda]['phone'] = this.userForm.userPhone;
            this.userData[userda]['QQ'] = this.userForm.userQQ;
            this.userData[userda]['address'] = this.userForm.userAdd;

            this.userForm.name = this.userData[userda]['userName'];
            this.userForm.email = this.userData[userda]['Email'];
            this.userForm.phone = this.userData[userda]['phone'];
            this.userForm.qq = this.userData[userda]['QQ'];
            this.userForm.add = this.userData[userda]['address'];
          }
        },
    }
</script>

<style scoped>

</style>
