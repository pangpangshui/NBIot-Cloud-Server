<template>
  <el-header style="height: 100px;">
    <div>
      <h1 class="hlogo">
        <router-link to="/">
          <img src="./../assets/images/logo.png" alt="NB-Iot Cloud" class="logo"></img>
        </router-link>
      </h1>
      <ul class="nav">
        <li class="nav-item">
          <el-input v-model="input" placeholder="搜索" suffix-icon="el-icon-search"></el-input>
        </li>
        <li class="nav-item">
          <!--<router-link to="/login">登录</router-link>-->
          <!--<router-link to="/login">-->

          <el-dropdown>
            <span class="el-dropdown-link">{{nickName}}</span>
            <i class="el-icon-arrow-down el-icon--right" icon="el-icon-arrow-down"></i>
            <el-dropdown-menu slot="dropdown" >
              <router-link to="/users/login">
                <el-dropdown-item>注销</el-dropdown-item>
              </router-link>
              <router-link to="/backmangementHome">
                <el-dropdown-item>云平台</el-dropdown-item>
              </router-link>
            </el-dropdown-menu>
          </el-dropdown>


          <!--</router-link>-->
        </li>
      </ul>

    </div>
  </el-header>
</template>

<script>
  import bus from './../API/bus'
  export default {
    name: "nb-manage-header",
    data() {
      return {
        input: '',
        nickName: ''
      }
    },
    created() {
      bus.$on('setNickName', (text) => {
        console.log(text);
        this.nickName = text;
      })

      bus.$on('goto', (url) => {
        if (url === '/login') {
          localStorage.removeItem('userName');
        }
        this.$router.push(url);
      })
    },
    mounted() {
      let user = sessionStorage.userName;
      if (user) {
        this.nickName = user || '';
      }
    }
  }
</script>

<style scoped>

</style>

